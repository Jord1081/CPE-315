#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Assembler.h"

#define OUTFILE_NAME "output.asm"

int main(int argc, char **argv) {
   AssembleData data;
   char *outFile;

   if (argc < 1 || argc > 2) {
      printf("Useage: %s [filename]\n", argv[0]);
      return 1;
   }
   if (argc == 2)
      outFile = argv[2];
   else
      outFile = OUTFILE_NAME;

   AssemblerInit(&data, argv[1], outFile);
   BuildTables(&data);
   CheckTables(data);

   return 0;
}
   /*
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
   */
