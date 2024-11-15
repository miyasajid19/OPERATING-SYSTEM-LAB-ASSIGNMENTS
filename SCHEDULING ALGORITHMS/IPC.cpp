#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;
int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[50];

    if (pipe(pipefd) == -1) {
        cerr << "Pipe failed!" << endl;
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    } else if (pid > 0) { // Parent process
        close(pipefd[0]); // Close reading end
        const char *message = "Hello from parent process!";
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
    } else { // Child process
        close(pipefd[1]); // Close writing end
        read(pipefd[0], buffer, sizeof(buffer));
        cout << "Child received: " << buffer << endl;
        close(pipefd[0]);
    }

    return 0;
}
