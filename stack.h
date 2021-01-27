#ifndef STACK_H
#define STACK_H

#include "token.h"

typedef struct stack_struct {
  int size;
  int top;
  Token *tokens;
} Stack;

Stack* createStack ();
void push (Stack*, Token);
void pop (Stack*);
int find (Stack*, Token);

#endif
