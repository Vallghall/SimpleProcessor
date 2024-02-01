#include "simple_computer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// RAM of a Simple Computer
int32_t *sc_memory; 
// Registers of a Simple Computer
// From right to left:
// -- 15 bits are Accumulator
// -- 7 bits are cmd counter
// -- 5 bits are a Flag Register
int32_t sc_registers;

#define SC_SET_REG_FLAG(flag) (sc_registers = sc_registers | flag)

int sc_memoryInit() {
  if (sc_memory != NULL) return -1;
  
  sc_memory = (int32_t*)calloc(RAM_SIZE, sizeof(int32_t));
  return 0;
}

int sc_memorySet(int address, int value) {
  if (address < 0 || RAM_SIZE <= address) {
    SC_SET_REG_FLAG(FMASK_OUT_OF_MEM_BORDERS);
    return -1;
  };

  sc_memory[address] = value;
  return 0;
}

int sc_memoryGet(int address, int *value) {
  if (address < 0 || RAM_SIZE <= address) {
    SC_SET_REG_FLAG(FMASK_OUT_OF_MEM_BORDERS);
    return -1;
  };

  *value = sc_memory[address];
  return 0;
}

int sc_memorySave(const char *filename) {
  FILE *f = fopen(filename, "w");
  if (f == NULL) {
    perror("failed to open file");
    return -1;
  }

  int written = fwrite(sc_memory, sizeof(int32_t), RAM_SIZE, f);
  fclose(f);
  
  if (written != RAM_SIZE) {
    perror("failed to write memory state to file");
    return -1;
  }

  return 0;
}

int sc_memoryLoad(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("failed to open file for reading");
    return -1;
  }

  int read = fread(sc_memory, sizeof(int32_t), RAM_SIZE, f);
  fclose(f);

  if (read != RAM_SIZE) {
    perror("failed to load content into the memory");
    return -1;
  }

  return 0;
}

int sc_regInit() {
  if (sc_registers != NULL) {
    perror("Registers already initialized");
    return -1;
  }

  return sc_registers = 0;
}

int sc_regSet(int registr, int value) {
  if (value < 0 || value > 1) {
    perror("incorrect value");
    return -1;
  }

  switch (registr) {
    case 0: SC_SET_REG_FLAG(F_ILLEGAL_CMD);        break;
    case 1: SC_SET_REG_FLAG(F_TIMPULSE_IGNORE);    break;
    case 2: SC_SET_REG_FLAG(F_OUT_OF_MEM_BORDERS); break;
    case 3: SC_SET_REG_FLAG(F_ZERO_DIVISION);      break;
    case 4: SC_SET_REG_FLAG(F_OVERFLOW);           break;
    default: perror("Invalid register num");   return -1;
  }

  return 0;
}

int sc_commandEncode(int command, int operand, int *value) {
  if (operand < 0 || operand > UINT8_MAX) {
    perror("Incorrect operand value");
    return -1;
  }

  // TODO: Check command later

  int tmp = 0;
  tmp = tmp | (command << CMD_SHIFT) | operand;
  *value = tmp;

  return 0;
}

int sc_commandDecode(int value, int *command, int *operand) {
  int tmp = value & 0xFF;
  *operand = tmp;

  tmp = (value >> CMD_SHIFT) & 0xFF;
  // TODO: Check command later
  *command = tmp;

  return 0;
}
