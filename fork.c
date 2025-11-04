#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

  printf("Fork demo starting.\n");

  // Use fork() to create a new process
  pid_t pid = fork();
  
  
  
  return 0;
}

