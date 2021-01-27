/*
 * Compiler Project
 * UMSL - CS 4280
 * December 10, 2020
 * Jordan Lanius - jordan.lanius@gmail.com
 *
 * - errhandler.c -
 * This file contains functions to perform different
 * types of error handling.
 * Exits the process when an error occurs.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

char errString[100];

// Outputs error if one is placed in errno
void errHandlerP () {
  if (errno != 0) {
    perror(errString);
    exit(EXIT_FAILURE);
  }
}

// Outputs error text in proper format
void errHandlerF (char *errorText) {
  fprintf(stderr, "%s: %s\n", errString, errorText);
  exit(EXIT_FAILURE);
}

// Allows the main function to set errString
void setErrString(char *exe) {
  snprintf(errString, sizeof errString, "%s: Error", exe);
}
