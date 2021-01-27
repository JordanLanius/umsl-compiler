/*
 * Compiler Project
 * UMSL - CS 4280
 * December 10, 2020
 * Jordan Lanius - jordan.lanius@gmail.com
 *
 * - tree.c -
 * This file assists in constructing a parse tree.
 * It also outputs the tree in a preorder traversal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bnf.h"
#include "errhandler.h"
#include "tree.h"
#include "token.h"

// Function Prototype
void outputNode (FILE*, Node*, int);

// Create a new node
Node* createNode (NonterminalID nonterm) {
  Node* newNode = malloc(sizeof(Node));

  newNode->nonterminal = nonterm;
  newNode->numChildren = 0;
  newNode->numTokens = 0;

  return newNode;
}

// Add a child node to a parent node
void addChild (Node* node, Node* child) {
  if (child != NULL) {
    if (node->numChildren < MAX_CHILDREN) {
      node->children[node->numChildren] = child;
      node->numChildren++;
    } else {
      errHandlerF("Too many children in a node.");
    }
  }
}

// Add a token to a node's list of tokens
void addToken (Node* node, Token tkn) {
  if (node->numTokens < MAX_TOKENS) {
    node->tokens[node->numTokens] = tkn;
    node->numTokens++;
  } else {
    errHandlerF("Too many tokens in a node.");
  }
}

// Print preorder traversal of the tree
void printPreorder (FILE *output, Node *root, int depth) {
  if (root != NULL) {
    outputNode(output, root, depth);

    int i;
    for (i = 0; i < root->numChildren; i++) {
      printPreorder(output, root->children[i], depth+1);
    }
  }
}

// Deconstruct the tree, freeing the memory it claimed
void freeTree (Node *root) {
  if (root != NULL) {
    int i;
    for (i = 0; i < root->numChildren; i++) {
      freeTree(root->children[i]);
    }

    free(root);
  }
}

// Print the contents of a node to output
void outputNode (FILE *output, Node *node, int depth) {
  int i;

  char indent[100] = "";
  for (i = 0; i < depth; i++) {
    strcat(indent, "  ");
  }

  char tkns[100] = "";
  for (i = 0; i < node->numTokens; i++) {
    strcat(tkns, " ");
    strcat(tkns, node->tokens[i].instance);
  }

  fprintf(output, "%s%s:%s\n", indent, NONTERM_NAMES[node->nonterminal], tkns);
}
