#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include <fcntl.h>
#include <semaphore.h>

int main(void) {
  pid_t pid = fork();
  if (pid) {
    // Parent
    for (uint_fast8_t i = 0; i < 10; ++i) {
      sleep(1);
      printf("Parent loop %"PRIuFAST8"\n", i);
    }
  } else {
    // Child
    for (uint_fast8_t i = 0; i < 10; ++i) {
      printf("Child loop %"PRIuFAST8"\n", i);
    }
  }
}

