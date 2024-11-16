#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MSG_KEY 1234  // Unique key for message queue
#define MSG_SIZE 100  // Max message size

// Message structure for message queue
struct message {
    long msg_type;        // Message type, must be > 0
    char msg_text[MSG_SIZE];  // Message content
};

// Parent Process
void parent_process(int msgid) {
    struct message msg;
    msg.msg_type = 1;  // Message type for the child process
    
    // Sending a few messages to the queue
    for (int i = 0; i < 5; ++i) {
        sprintf(msg.msg_text, "Message #%d from parent", i + 1);
        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }
        printf("Parent sent: %s\n", msg.msg_text);
        sleep(1);  // Simulate some delay between messages
    }

    // Send a termination message
    msg.msg_type = 2;  // A special message type to indicate termination
    sprintf(msg.msg_text, "Parent terminating the process");
    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }
    printf("Parent sent: %s\n", msg.msg_text);
}

// Child Process
void child_process(int msgid) {
    struct message msg;
    
    while (1) {
        // Receive a message
        if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 0, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }
        
        printf("Child received: %s\n", msg.msg_text);

        // If it's the termination message, exit the loop
        if (msg.msg_type == 2) {
            printf("Child received termination message. Exiting...\n");
            break;
        }
    }
}

// Main function
int main() {
    int msgid;

    // Create a message queue with a unique key (MSG_KEY)
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Fork to create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {
        // Parent process
        parent_process(msgid);
    } else {
        // Child process
        child_process(msgid);
    }

    // Clean up: remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    return 0;
}
