/*
 * Compiler Project
 * UMSL - CS 4280
 * December 10, 2020
 * Jordan Lanius - jordan.lanius@gmail.com
 *
 * - main.c -
 * This file contains the main function that opens files based on the command line.
 * It then calls the parser and runs parse tree through static semantics verification.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "errhandler.h"
#include "parser.h"
#include "generator.h"
#include "tree.h"

// Function Prototypes
FILE *openFile (char*, char*, char*);

// Global Constants
static const int FILENAME_LENGTH = 100;
static const char IN_SUFFIX[10] = ".fs";
static const char OUT_DFLT[15] = "kb";
static const char OUT_SUFFIX[10] = ".asm";

/* Main Function */
int main (int argc, char *argv[]) {
  // Variables
  char filename[FILENAME_LENGTH];
  char outName[FILENAME_LENGTH];
  FILE* inFile;
  FILE* outFile;
  Node* parseTree;

  // Initiate errString with program name
  setErrString(argv[0]);

  // Read arguments and open input file
  if (argc > 2) {
    errHandlerF("Too many arguments.");
  } else if (argc == 2) {
    strcpy(filename, argv[1]);
    inFile = openFile(filename, (char*)IN_SUFFIX, "r");
  } else {
    inFile = stdin;
  }

  // Call parser
  parseTree = parser(inFile);

  // Close input file
  fclose(inFile);

  // Open output file
  if (argc == 2) {
    sprintf(outName, "%s%s", filename, OUT_SUFFIX);
  } else {
    sprintf(outName, "%s%s", OUT_DFLT, OUT_SUFFIX);
  }
  outFile = openFile(outName, "", "w");

  // Generate .asm code
  generator(parseTree, outFile);

  printf("%s\n", outName);

  // Cleanup
  freeTree(parseTree);
  fclose(outFile);

  return EXIT_SUCCESS;
}

// Handles opening a file that is missing a suffix
FILE* openFile (char *name, char *suffix, char *mode) {
  FILE* file = NULL;
  char filename[strlen(name) + strlen(suffix)];

  strcpy(filename, name);
  strcat(filename, suffix);

  file = fopen(filename, mode);

  if (file == NULL) {
    errHandlerP();
  }

  return file;
}
