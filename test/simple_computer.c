#include "simple_computer.h"
#include <stdio.h>

int main() {
  printf("START");
  sc_memoryInit();
  sc_memorySet(0, 31);

  int value;
  sc_memoryGet(0, &value);
  printf("Got saved value: %d\n", value);
  
  return sc_memorySave("test.txt");
}
