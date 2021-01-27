#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include "bnf.h"
#include "token.h"

static const int MAX_CHILDREN = 5;
static const int MAX_TOKENS = 5;

typedef struct node_struct {
  NonterminalID nonterminal;
  struct node_struct *children[5];
  Token tokens[5];
  int numChildren;
  int numTokens;
} Node;

Node* createNode (NonterminalID);
void addChild (Node*, Node*);
void addToken (Node*, Token);
bool containsToken (Node*, Token);
void printPreorder (FILE*, Node*, int);
void freeTree (Node*);

#endif
