/*
 * Compiler Project
 * UMSL - CS 4280
 * December 10, 2020
 * Jordan Lanius - jordan.lanius@gmail.com
 *
 * - stack.c -
 * This file assist in constructing and modifying a stack.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errhandler.h"
#include "stack.h"
#include "token.h"

// Function Prototypes
bool isFull (Stack*);
bool isEmpty (Stack*);

// Constants
const int MAX_ITEMS = 100;

// Initialize a new stack
Stack* createStack () {
  Stack *variables = (Stack*) malloc(sizeof(Stack));

  variables->size = MAX_ITEMS;
  variables->top = -1;
  variables->tokens = (Token*) malloc(sizeof(Token) * MAX_ITEMS);

  return variables;
}

// Push a new token onto the stack
void push (Stack *variables, Token token) {
  // Check for stack overflow
  if (isFull(variables)) {
    errHandlerF("Stack Overflow");
  }

  variables->top++;
  variables->tokens[variables->top] = token;
}

// Remove the top token from the stack
void pop (Stack *variables) {
  // Check for stack underflow
  if (isEmpty(variables)) {
    errHandlerF("Stack Underflow");
  }

  variables->top--;
}

// Returns the distance from the top of stack of a matching variable
int find (Stack *variables, Token token) {
  int index;
  for (index = variables->top; index >= 0; index--) {
    if (strcmp(variables->tokens[index].instance, token.instance) == 0) {
      return (variables->top - index);
    }
  }

  return -1;
}

// Check if the stack is full
bool isFull (Stack *variables) {
  if (variables->top == (variables->size - 1)) {
    return true;
  } else {
    return false;
  }
}

// Check if the stack is empty
bool isEmpty (Stack *variables) {
  if (variables->top == -1) {
    return true;
  } else {
    return false;
  }
}
