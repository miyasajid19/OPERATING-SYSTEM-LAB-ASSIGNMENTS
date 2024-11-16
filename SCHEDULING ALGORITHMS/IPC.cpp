#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;

int main() {
    int pipefd1[2];  // Pipe 1 for Parent -> Child
    int pipefd2[2];  // Pipe 2 for Child -> Parent
    pid_t pid;
    char buffer[100];

    // Create the first pipe (Parent -> Child)
    if (pipe(pipefd1) == -1) {
        cerr << "Pipe1 failed!" << endl;
        return 1;
    }

    // Create the second pipe (Child -> Parent)
    if (pipe(pipefd2) == -1) {
        cerr << "Pipe2 failed!" << endl;
        return 1;
    }

    // Fork the process
    pid = fork();
    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    if (pid > 0) {  // Parent Process
        close(pipefd1[0]); // Close read end of pipe1 (not needed by parent)
        close(pipefd2[1]); // Close write end of pipe2 (not needed by parent)

        const char *message1 = "Hello from parent!";
        write(pipefd1[1], message1, strlen(message1) + 1);  // Send to child

        // Read response from the child
        read(pipefd2[0], buffer, sizeof(buffer));
        cout << "Parent received from child: " << buffer << endl;

        close(pipefd1[1]); // Close write end of pipe1
        close(pipefd2[0]); // Close read end of pipe2
    }
    else {  // Child Process
        close(pipefd1[1]); // Close write end of pipe1 (not needed by child)
        close(pipefd2[0]); // Close read end of pipe2 (not needed by child)

        // Read message from the parent
        read(pipefd1[0], buffer, sizeof(buffer));
        cout << "Child received from parent: " << buffer << endl;

        const char *message2 = "Hello from child!";
        write(pipefd2[1], message2, strlen(message2) + 1);  // Send to parent

        close(pipefd1[0]); // Close read end of pipe1
        close(pipefd2[1]); // Close write end of pipe2
    }

    return 0;
}
