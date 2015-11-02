#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#define BYTE_SHIFT_3 24
#define REG_BIT_WIDTH 5
#define TYPES_ARRAY_SIZE 21
#define R_TYPE_SIZE 10
#define I_TYPE_SIZE 9
#define J_TYPE_SIZE 2

typedef struct Types {
   char *name;
   unsigned int data;
} Types;

typedef struct Label {
   char *name;
   int address;
} Label;

typedef struct Data {
   int address;
   char *data;
   int width;
   int size;
} Data;

enum Instructions { ADD, ANDI, OR, ORI, ADDU, ADDIU, SLL, SRL, SRA, SLTU,
 SUB, SLTIU, BEQ, BNE, LW, SW, LUI, J, JR, JAL };

extern const char * const InstructionNames[];
extern const int FunctionCodes[];
extern const int OpCodes[];

Types FindType(char *);
Types *BuildTypesArray();
void FillRegister(Types *, unsigned int, int);


#endif
