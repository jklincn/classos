#include "common.h"

__attribute__((aligned(16))) char stack[4096];

void print_task() {
  char message[] = "this is task [1]!\n";
  while (1)
    for (int i = 0; *(message + i) != '\0'; i++) {
      uartputc(*(message + i));
    }
}

void main() {
  char message[] = "Hello, OS!\n";
  uartinit();
  for (int i = 0; *(message + i) != '\0'; i++) {
    uartputc(*(message + i));
  }
  create_task(print_task);
  scheduler();
}
