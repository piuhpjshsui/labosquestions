#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t child_pid;

    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process
        close(fd[1]);  // Close the write end of the pipe

        char buffer[50];
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        close(fd[0]);  // Close the read end of the pipe
    } else {
        // Parent process
        close(fd[0]);  // Close the read end of the pipe

        char message[] = "Hello, child!";
        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);  // Close the write end of the pipe
    }

    return 0;
}
