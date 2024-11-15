#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
using namespace std;
struct Message {
    long msgType;
    char text[100];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    Message msg;

    if (fork() == 0) { // Child process - Receiver
        msgrcv(msgid, &msg, sizeof(msg), 1, 0);
        cout << "Received message: " << msg.text << endl;
    } else { // Parent process - Sender
        msg.msgType = 1;
        strcpy(msg.text, "Hello from parent process through message queue!");
        msgsnd(msgid, &msg, sizeof(msg), 0);
    }

    msgctl(msgid, IPC_RMID, NULL); // Delete the message queue
    return 0;
}
