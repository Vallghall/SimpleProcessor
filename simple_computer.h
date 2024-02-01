#ifndef SIMPLE_COMPUTER_H
#define SIMPLE_COMPUTER_H

// --- Registers ---

// Implementation should define *sc_registers* global var

// 1st bit (from left) - F_OVERFLOW
// 2nd bit - F_ZERO_DIVISION
// 3rd bit - F_OUT_OF_MEM_BORDERS
// 4th bit - F_TIMPULSE_IGNORE
// 5th bit - F_ILLEGAL_CMD

#define SC_CMD_COUNTER   ((sc_registers >> 15) & 0b1111111)
#define SC_ACUMULATOR    (sc_registers & 0x8FFF)
#define SC_FLAG_REGISTER (sc_registers >> 21)

#define F_ILLEGAL_CMD        (SC_FLAG_REGISTER & 1)
#define F_TIMPULSE_IGNORE    (SC_FLAG_REGISTER & 2)
#define F_OUT_OF_MEM_BORDERS (SC_FLAG_REGISTER & 0b100)
#define F_ZERO_DIVISION      (SC_FLAG_REGISTER & 0b1000)
#define F_OVERFLOW           (SC_FLAG_REGISTER & 0b10000)

#define FMASK_ILLEGAL_CMD        (1 << 21)
#define FMASK_TIMPULSE_IGNORE    (1 << 22)
#define FMASK_OUT_OF_MEM_BORDERS (1 << 23)
#define FMASK_ZERO_DIVISION      (1 << 24)
#define FMASK_OVERFLOW           (1 << 25)


// !-- Registers --!

// --- Commands ---

#define CMD_SHIFT 8

// ---- I/O Commands ----

#define SC_CMD_READ 0x0A

// ---- I/O Commands ----

// !-- Commands --!

// --- RAM functions ---

#define RAM_SIZE 100

// Initializes Simple Computer RAM
// setting all cells to zero-value
int sc_memoryInit();

// Sets the cell at given address to value.
// If address is illegal then OUT_OF_MEM_BORDERS
// flag is set and a negative integer is returned
int sc_memorySet(int address, int value);

// Sets value at ptr location to a value
// from the location pointet to by address
// variable. If address is illegal then OUT_OF_MEM_BORDERS
// flag is set and a negative integer is returned
int sc_memoryGet(int address, int *value);

// Saves memory content to a file
// with a given filename
int sc_memorySave(const char *filename);

// Loads data from a file from the given
// filename into SC memory
int sc_memoryLoad(const char *filename);

// Initializes flag refister with a zero value
int sc_regInit(void);

// Set the value of a given flag registry.
// If the registr or the value are illegal
// a negative integer is returned.
int sc_regSet(int registr, int value);

// Returns the value of a given registr
// through a given ptr.If registr is illegal
// then a negative integer is returned
int sc_regGet(int registr, int *value);

// Encodes a command and operand and sets result
// to a given value ptr.If command or operand is
// illegal than a negative integer is returned
int sc_commandEncode(int command, int operand, int *value);

// Decodes value as Simple Computer cmd. If decoding is
// impossible then flag E (illegal cmd) is set and a
// negative integer is returned
int sc_commandDecode(int value, int *command, int *operand);

// --- RAM funstions ---

#endif // SIMPLE_COMPUTER_H
