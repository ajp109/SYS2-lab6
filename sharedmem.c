#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <inttypes.h>
#include <fcntl.h>
#include <semaphore.h>

#include <sys/mman.h>

#define MESSAGE_SIZE 100

int main() {
  
  sem_t *sem = sem_open("/sharedmem", O_CREAT| O_EXCL, 0600, 0);
  sem_unlink("/sharedmem");

  // Allocate some memory to be used by both processes
  char *msg_ptr = calloc(1, MESSAGE_SIZE);
  
  // Put a default message into the memory - this should be overwritten
  printf("Writing default message to memory at %p\n", (void *)msg_ptr);
  strncpy(msg_ptr, "[default message]", MESSAGE_SIZE);
  msg_ptr[MESSAGE_SIZE-1] = '\0';
  
  
  // Fork a new process
  pid_t pid = fork();
  if (pid) { // Parent process
    // Write a message to the shared memory
    printf("Parent is writing to memory at %p\n", (void *)msg_ptr);
    strncpy(msg_ptr, "Hello from the parent", MESSAGE_SIZE);
    msg_ptr[MESSAGE_SIZE-1] = '\0';

    // Signal the semaphore
    sem_post(sem);

    // Wait for the child to terminate
    wait(NULL);

    // Read the child's response
    printf("Parent reads child's response: '%s'\n", msg_ptr);
      
    // Close the semaphore and free the shared memory
    sem_close(sem);
    free(msg_ptr);
  } else {
    // CHILD PROCESS
    // Wait for the semaphore
    sem_wait(sem);
    
    // Read the parent's message
    printf("Child is reading from memory at %p\n", msg_ptr);
    printf("Child reads parent's message: '%s'\n", msg_ptr);
      
    // Child writes a new message to shared memory.
    printf("Child is writing to memory at %p\n", (void *)msg_ptr);
    strncpy(msg_ptr, "Reply from the child", MESSAGE_SIZE);
    msg_ptr[MESSAGE_SIZE-1] = 0;
          
    // Close the semaphore and free the shared memory
    sem_close(sem);
    free(msg_ptr);
  }
  
  return 0;
}
