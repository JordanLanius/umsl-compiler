#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

typedef enum {
  // End-of-File
  EOF_tk,

  // Identifiers and Numbers
  IDENT_tk, NUM_tk,

  // Operators
  ASSIGN_tk, GTEQ_tk, LTEQ_tk, EQUAL_tk, COLON_tk,
  PLUS_tk, MINUS_tk, MULT_tk, DIV_tk, MOD_tk, DOT_tk,

  // Delimiters
  OPPAREN_tk, CLPAREN_tk, COMMA_tk, OPBRACE_tk, CLBRACE_tk,
  SEMICOL_tk, OPBRACK_tk, CLBRACK_tk,

  // Keywords
  START_tk, STOP_tk, ITER_tk, VOID_tk, INT_tk, EXIT_tk, SCANF_tk,
  PRINTF_tk, MAIN_tk, IF_tk, THEN_tk, LET_tk, DATA_tk, FUNC_tk
} TokenID;

typedef struct token_struct {
  TokenID id;
  char instance[10];
  int lineNum;
} Token;

static const int NUM_BASIC_TK = 22;
static const int NUM_KEYWORD_TK = 14;
static const int NUM_OPERATOR_TK = 11;

// Output names for every token
static const char TOKEN_NAMES[36][20] = {
  // End-of-File
  "End-of-File",

  // Identifiers and Integers
  "Identifier", "Integer",

  // Operators
  "'=' Operator", "'=>' Operator", "'=<' Operator", "'==' Operator", "':' Operator",
  "'+' Operator", "'-' Operator", "'*' Operator", "'/' Operator", "'%' Operator", "'.' Operator",

  // Delimiters
  "Open Parenthesis", "Close Parenthesis", "Comma", "Open Brace", "Close Brace",
  "Semicolon", "Open Bracket", "Close Bracket",

  // Keywords
  "'start' Keyword", "'stop' Keyword", "'iter' Keyword", "'void' Keyword",
  "'int' Keyword", "'exit' Keyword", "'scanf' Keyword",
  "'printf' Keyword", "'main' Keyword", "'if' Keyword", "'then' Keyword",
  "'let' Keyword", "'data' Keyword", "'func' Keyword"
};

// List of keywords
static const char KEYWORDS[14][10] = {
  "start", 
  "stop", 
  "iter",
  "void",
  "int",
  "exit",
  "scanf",
  "printf",
  "main",
  "if",
  "then",
  "let",
  "data",
  "func"
};

#endif
