#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
   
    key_t key = ftok("shared_memory_example", 65);
    
   
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
   

    char *shmaddr = (char*)shmat(shmid, (void*)0, 0);
    
  
    strcpy(shmaddr, "Hello, Shared Memory!");
    
    
    shmdt(shmaddr);
  
    int child_pid = fork();
    
    if (child_pid == 0) {
         char *child_shmaddr = (char*)shmat(shmid, (void*)0, 0);
        printf("Child process read: %s\n", child_shmaddr);
        shmdt(child_shmaddr);
    }
    
   
    wait(NULL);

    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
