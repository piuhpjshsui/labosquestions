#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == 0) {
        // This is the child process
        printf("Child process executing 'date' command:\n");
        execl("/bin/date", "date", NULL);
        perror("execl"); // This line will be reached only if execl fails
        exit(1);
    } else if (child_pid > 0) {
        // This is the parent process
        printf("Parent process executing 'ls' command:\n");
        execl("/bin/ls", "ls", NULL);
        perror("execl"); // This line will be reached only if execl fails
        exit(1);
    } else {
        // Forking failed
        perror("fork");
        exit(1);
    }

    return 0;
}
