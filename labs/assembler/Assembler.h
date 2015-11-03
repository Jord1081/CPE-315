#ifndef ASSEMBLER_H
#define ASSEMBLER_H

typedef struct Data Data;
typedef struct Label Label;
typedef struct Types Types;

typedef struct AssembleData {
   Types *typeTable; // List of Types to identify instructions.
   Label *labelTable; // List of Labels to identify corresponding addresses.
   int numLabels; // Total number of labels.
   Data *dataTable; // List of user defined data from .data section.
   int numData; // Total number of data elements.
   char *inFile;
   char *outFile;
} AssembleData;

extern const char * const InstructionNames[];
extern const int FunctionCodes[];
extern const int OpCodes[];

void AssemblerInit(AssembleData *data, char *inFile, char *outFile);
void BuildTables();
void Cleanup(AssembleData *data);
void CheckTables(AssembleData data);

#endif
