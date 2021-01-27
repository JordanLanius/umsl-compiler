/*
 * Compiler Project
 * UMSL - CS 4280
 * December 12, 2020
 * Jordan Lanius - jordan.lanius@gmail.com
 *
 * - generator.c -
 * This file contains a code generator that converts
 * a parse tree into .asm code. As it generates code,
 * it verifies the code's static semantics.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bnf.h"
#include "errhandler.h"
#include "generator.h"
#include "stack.h"
#include "token.h"
#include "tree.h"

// Function prototypes
void recGen (Node*, int*);
char* newName (NameType);
void newScope (Node*);
void testVar (Token, int*);
int testIdent (Token);

// Variables
FILE *outFile;
Stack *variables;
static int variableCount = 0;
static int labelCount = 0;
static char name[NAME_LENGTH];

// Initial generator function
void generator (Node *root, FILE *out) {
  outFile = out;

  int globalCount = 0;

  // Initialize stack
  variables = createStack();

  // Traverse each node in parse tree
  recGen(root, &globalCount);

  // Finish off the code
  fprintf(outFile, "STOP\n");
  int i;
  for (i = 0; i < variableCount; i++) {
    fprintf(outFile, "T%d 0\n", i);
  }

  // Free memory used for the stack
  free(variables);
}

// Recursive traversal
void recGen (Node *root, int *varCount) {
  // Temporary storage
  char label1[NAME_LENGTH];
  char label2[NAME_LENGTH];
  char argR[NAME_LENGTH];

  // Return immediately if the node is empty
  if (root == NULL) {
    return;
  }

  // Perform different actions based on the node label
  switch (root->nonterminal) {
    case BLOCK_nt:
      newScope(root);
      break;

    case VARS_nt:
      if ((root->numTokens > 0) && (root->tokens[0].id == IDENT_tk)) {
        testVar(root->tokens[0], varCount);
        push(variables, root->tokens[0]);
        fprintf(outFile, "PUSH\n");
        fprintf(outFile, "LOAD %s\n", root->tokens[2].instance);
        fprintf(outFile, "STACKW 0\n");
        *varCount += 1;

        recGen(root->children[0], varCount);
      }
      break;

    case EXPR_nt:
      if (root->numTokens > 0) {
        recGen(root->children[1], varCount);
        strcpy(argR, newName(VAR));
        fprintf(outFile, "STORE %s\n", argR);
        recGen(root->children[0], varCount);

        if (root->tokens[0].id == DIV_tk) {
          fprintf(outFile, "DIV %s\n", argR);
        } else if (root->tokens[0].id == MULT_tk) {
          fprintf(outFile, "MULT %s\n", argR);
        }
      } else {
        recGen(root->children[0], varCount);
      }
      break;

    case N_nt:
      if (root->numTokens > 0) {
        recGen(root->children[1], varCount);
        strcpy(argR, newName(VAR));
        fprintf(outFile, "STORE %s\n", argR);
        recGen(root->children[0], varCount);

        if (root->tokens[0].id == PLUS_tk) {
          fprintf(outFile, "ADD %s\n", argR);
        } else if (root->tokens[0].id == MINUS_tk) {
          fprintf(outFile, "SUB %s\n", argR);
        }
      } else {
        recGen(root->children[0], varCount);
      }
      break;

    case A_nt:
      recGen(root->children[0], varCount);
      if ((root->numTokens > 0) && (root->tokens[0].id == MOD_tk)) {
        fprintf(outFile, "MULT -1\n");
      }
      break;

    case R_nt:
      if (root->numTokens > 0) {
        if (root->tokens[0].id == IDENT_tk) {
          fprintf(outFile, "STACKR %d\n", testIdent(root->tokens[0]));
        } else if (root->tokens[0].id == NUM_tk) {
          fprintf(outFile, "LOAD %s\n", root->tokens[0].instance);
        }
      } else {
        recGen(root->children[0], varCount);
      }
      break;

    case IN_nt:
      strcpy(argR, newName(VAR));
      fprintf(outFile, "READ %s\n", argR);
      fprintf(outFile, "LOAD %s\n", argR);
      fprintf(outFile, "STACKW %d\n", testIdent(root->tokens[0]));
      break;

    case OUT_nt:
      recGen(root->children[0], varCount);
      strcpy(argR, newName(VAR));
      fprintf(outFile, "STORE %s\n", argR);
      fprintf(outFile, "WRITE %s\n", argR);
      break;

    case IF_nt:
      recGen(root->children[2], varCount);
      strcpy(argR, newName(VAR));
      fprintf(outFile, "STORE %s\n", argR);
      recGen(root->children[0], varCount);
      fprintf(outFile, "SUB %s\n", argR);
      strcpy(label1, newName(LABEL));

      switch (root->children[1]->tokens[0].id) {
        case LTEQ_tk:
          fprintf(outFile, "BRPOS %s\n", label1);
          break;
        case GTEQ_tk:
          fprintf(outFile, "BRNEG %s\n", label1);
          break;
        case EQUAL_tk:
          fprintf(outFile, "BRPOS %s\n", label1);
          fprintf(outFile, "BRNEG %s\n", label1);
          break;
        default:
          fprintf(outFile, "BRZERO %s\n", label1);
          break;
      }

      recGen(root->children[3], varCount);
      fprintf(outFile, "%s: NOOP\n", label1);
      break;

    case LOOP_nt:
      strcpy(label1, newName(LABEL));
      fprintf(outFile, "%s: NOOP\n", label1);
      recGen(root->children[2], varCount);
      strcpy(argR, newName(VAR));
      fprintf(outFile, "STORE %s\n", argR);
      recGen(root->children[0], varCount);
      fprintf(outFile, "SUB %s\n", argR);
      strcpy(label2, newName(LABEL));

      switch (root->children[1]->tokens[0].id) {
        case LTEQ_tk:
          fprintf(outFile, "BRPOS %s\n", label2);
          break;
        case GTEQ_tk:
          fprintf(outFile, "BRNEG %s\n", label2);
          break;
        case EQUAL_tk:
          fprintf(outFile, "BRPOS %s\n", label2);
          fprintf(outFile, "BRNEG %s\n", label2);
          break;
        default:
          fprintf(outFile, "BRZERO %s\n", label2);
          break;
      }

      recGen(root->children[3], varCount);
      fprintf(outFile, "BR %s\n", label1);
      fprintf(outFile, "%s: NOOP\n", label2);
      break;

    case ASSIGN_nt:
      recGen(root->children[0], varCount);
      fprintf(outFile, "STACKW %d\n", testIdent(root->tokens[0]));
      break;

    default: ;
      int i;
      for (i = 0; i < root->numChildren; i++) {
        recGen(root->children[i], varCount);
      }
      break;
  }
}

// Prepare a new scope for each <block> nonterminal
void newScope (Node *root) {
  int i;
  int varCount = 0;

  // Traverse through all child nodes
  for (i = 0; i < root->numChildren; i++) {
    recGen(root->children[i], &varCount);
  }

  // Remove local variables from stack when leaving scope
  for (; varCount > 0; varCount--) {
    pop(variables);
    fprintf(outFile, "POP\n");
  }
}

// Test if variable has been defined in current scope
void testVar (Token token, int *varCount) {
  if (*varCount > 0) {
    int stackLocation = find(variables, token);

    if ((stackLocation >= 0) && (stackLocation < *varCount)) {
      // Throw error if multiple definitions in scope
      char errText[100];
      sprintf(errText, "Line %d - Variable '%s' already defined in scope.",
              token.lineNum, token.instance);
      errHandlerF(errText);
    }
  }
}

// Test if variable has been defined earlier in program
int testIdent (Token token) {
  int location = find(variables, token);

  if (location == -1) {
    // Throw error if no definition found
    char errText[100];
    sprintf(errText, "Line %d - Variable '%s' not defined in scope.",
            token.lineNum, token.instance);
    errHandlerF(errText);
  }

  return location;
}

// Construct a new unique name
char* newName (NameType type) {
  if (type == VAR) {
    sprintf(name, "T%d", variableCount++);
  } else {
    sprintf(name, "L%d", labelCount++);
  }

  return name;
}
