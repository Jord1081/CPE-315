#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#define TYPES_ARRAY_SIZE = 21

typedef struct Types {
   char *name;
   unsigned int data;
} Types;

typedef struct Label {
   char *name;
   int address;
};

typedef struct Data {
   int address;
   char *data;
   int width;
   int size;
}

enum Instructions { ADD, ANDI, OR, ORI, ADDU, ADDIU, SLL, SRL, SRA, SLTU,
 SUB, SLTIU, BEQ, BNE, LW, SW, LUI, J, JR, JAL }

Types FindType(char *);
Types *BuildTypesArray();


#endif
