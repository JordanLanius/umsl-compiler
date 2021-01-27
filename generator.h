#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "tree.h"

#define NAME_LENGTH 20

typedef enum {
  VAR, LABEL
} NameType;

void generator (Node*, FILE*);

#endif
