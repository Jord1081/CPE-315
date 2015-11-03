#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Assembler.h"

#define BYTE_SHIFT_3 24
#define REG_BIT_WIDTH 5
#define TYPES_ARRAY_SIZE 21
#define R_TYPE_SIZE 10

#define I_TYPE_SIZE 9
#define J_TYPE_SIZE 2
#define OP_LEN 7
#define WORD_LEN 4

#define BUFF_SIZE 100

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

const char * const InstructionNames[] = {
   "add", "addu", "and", "jr", "or", "sll", "sltu", "sra", "srl", "sub",
   "andiu", "andi", "beq", "bne", "lui", "lw", "ori", "sltiu" "sw", "j",
   "jal"
};

const int FunctionCodes[] = {
   0x20, 0x21, 0x24, 0x08, 0x25, 0x00, 0x2B, 0x03, 0x02, 0x22 
};

const int OpCodes[] = {
   0x0C, 0x04, 0x05, 0x0F, 0x23, 0x0D, 0x0B, 0x2B, 0x02, 0x03
};

enum Instructions { ADD, ANDI, OR, ORI, ADDU, ADDIU, SLL, SRL, SRA, SLTU,
 SUB, SLTIU, BEQ, BNE, LW, SW, LUI, J, JR, JAL };

Types FindType(char *instruction) {
}

Types *BuildTypesArray() {
   int ndx;
   Types *ret = calloc(TYPES_ARRAY_SIZE, sizeof(Types));

   for (ndx = 0; ndx < TYPES_ARRAY_SIZE; ndx++)
      ret[ndx].name = (char *)InstructionNames[ndx];

   for (ndx = 0; ndx < R_TYPE_SIZE; ndx++)
      ret[ndx].data |= FunctionCodes[ndx];

   for (ndx = R_TYPE_SIZE; ndx < TYPES_ARRAY_SIZE; ndx++)
      ret[ndx].data |= OpCodes[ndx] << BYTE_SHIFT_3;

   return ret;
}

void AssemblerInit(AssembleData *data, char *inFile, char *outFile) {
   data->inFile = inFile;
   data->outFile = outFile;
   data->typeTable = BuildTypesArray();
   data->labelTable = NULL;

   data->numLabels = 0;
   data->dataTable = NULL;
   data->numData = 0;

}

void BuildTables(AssembleData *data) {
   char buf[BUFF_SIZE], *line, *token;
   int loc = 0;
   FILE *input;

   input = fopen(data->inFile, "r");
   assert(input != NULL);

   while (fgets(buf, BUFF_SIZE, input)) {
      line = strtok(buf, "#");
      if (strlen(line) > 1) {
         loc++;
         if (strpbrk(line, ":")) {
            token = strtok(line, ":");

            // Reallocate space for one more label and add to the end of table.
            data->labelTable = realloc(data->labelTable, sizeof(Label) * 
             ++data->numLabels);
            data->labelTable[data->numLabels - 1].name = malloc(strlen(token));

            strcpy(data->labelTable[data->numLabels - 1].name, token);
            data->labelTable[data->numLabels - 1].address = loc * WORD_LEN;
         }
      }
   }
   fclose(input);
}

void FillRegister(Types *type, unsigned int val, int pos) {
   
}

void Cleanup(AssembleData *data) {
}

void CheckTables(AssembleData data) {
   int ndx;
   for (ndx = 0; ndx < data.numLabels; ndx++)
      printf("Label: %s Address: %d\n", data.labelTable[ndx].name,
       data.labelTable[ndx].address);
}
