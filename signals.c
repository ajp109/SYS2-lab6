#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
  // Write a message to standard output using ONLY async-signal-safe functions
}

int main(void) {
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = sigint_handler;
  sigaction(SIGINT, &sa, NULL);

  printf("PID: %jd\n", (intmax_t)getpid());
  printf("Press Ctrl+C to send SIGINT.\n\n");

  uint32_t counter = 0;
  while (1) {
    printf("Running... Loop iteration: %d\n", ++counter);
    sleep(1);
  }
  
  return 0;
}

