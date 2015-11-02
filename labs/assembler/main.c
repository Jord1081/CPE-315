#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Assembler.h"

#define MAX_FILENAME 255
#define BUFF_SIZE 1000
#define OUTFILE_NAME "output.asm"
#define OP_LEN 7

int main() {
   char *filename, buf[BUFF_SIZE], *token, str[OP_LEN];
   Types *TypesTable = BuildTypesArray();
   FILE *fp, *out_file;
   unsigned int loc = 0;

   printf("Enter a filename:\n");
   scanf("%MAX_FILENAMEs", filename);

   // Read file of instructions

   fp = fopen(filename, "r");
   assert(fp != NULL);
   out_file = fopen(OUTFILE_NAME, "w");
   assert(out_file != NULL);

   // First pass to find lables
   while (fgets(buf, BUFF_SIZE, fp)) {
      token = strtok(buf, ":");
      if (token) {
         // Found a label so add it to the table.
      }
   }
   fclose(fp);

   // Second pass to parse instructions.
   fp = fopen(filename, "r");
   assert(fp != NULL);
   while (fgets(buf, BUFF_SIZE, fp)) {
      token = strtok(buf, " ");
      strncpy(str, buf, token - buf + 1);
      printf("Debug: OP is %s\n", str); // Print the operation for debugging.
      // Determine the instruction type.

      // Find number of lines of instructions and data.
   }
   fclose(fp);

   // Write output.

   fclose(out_file);
   free(TypesTable);
   return 0;
}
