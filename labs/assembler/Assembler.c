#include <stdio.h>
#include "Assembler.h"

#define MAX_FILENAME 255

const char *instructions[TYPES_ARRAY_SIZE] = {

}

Types FindType(char *) {
}

Types *BuildTypesArray() {
}

int main() {
   char *filename;
   char *InstructionNames[TYPES_ARRAY_SIZE] = {
      "add", "addu", "and", "jr", "or", "sll", "sltu", "sra", "srl", "sub",
      "andiu", "andi", "beq", "bne", "lui", "lw", "ori", "sltiu" "sw", "j",
      "jal"
   }

   printf("Enter a filename:\n");
   scanf("%MAX_FILENAMEs", &filename);

   // Read file of instructions

   FILE *fp = fopen(filename, "r");
   assert(fp != NULL);


   fclose(fp);

   // Define symbols


   // Generate object code
}
