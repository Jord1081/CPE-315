#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Assembler.h"

#define MAX_FILENAME 255

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

void FillRegister(Types *type, unsigned int val, int pos) {
   
}

int main() {
   char *filename;
   Types *TypesTable = BuildTypesArray();

   printf("Enter a filename:\n");
   scanf("%*s", MAX_FILENAME, &filename);

   // Read file of instructions

   FILE *fp = fopen(filename, "r");
   assert(fp != NULL);


   fclose(fp);

   // Define symbols


   // Generate object code


   free(TypesTable);
}
