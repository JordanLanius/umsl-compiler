/*
 * Compiler Project
 * UMSL - CS 4280
 * December 10, 2020
 * Jordan Lanius - jordan.lanius@gmail.com
 *
 * - parser.c -
 * This file contains a parser that produces an error
 * if the input doesn't fit the language.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errhandler.h"
#include "scanner.h"
#include "token.h"
#include "tree.h"

// Function Prototypes
Node* program();
Node* block();
Node* vars();
Node* expr_1();
void expr_2();
Node* N_1();
void N_2();
Node* A();
Node* R();
Node* stats();
Node* mStat();
Node* stat();
Node* in();
Node* out();
Node* if_par();
Node* loop();
Node* assign();
Node* RO();
void parseError();

// Variables
FILE *inFile;
Token token;
char expectedTks[100] = "";

/* Main parser function */

Node* parser (FILE *input) {
  inFile = input;

  initializeScanner(inFile);
  token = scanner(inFile);

  Node *parseTree = program();

  if (token.id != EOF_tk) {
    sprintf(expectedTks, "%s", TOKEN_NAMES[EOF_tk]);
    parseError();
  }

  return parseTree;
}

/* Nonterminal functions */

// <program> -> start <vars> main <block> stop
Node* program () {
  Node *program_nd = createNode(PROGRAM_nt);

  if (token.id == START_tk) {
    token = scanner(inFile);

    addChild(program_nd, vars());

    if (token.id == MAIN_tk) {
      token = scanner(inFile);

      addChild(program_nd, block());

      if (token.id == STOP_tk) {
        token = scanner(inFile);

        return program_nd; // Successful parse
      } else {
        sprintf(expectedTks, "%s", TOKEN_NAMES[STOP_tk]);
        parseError();
      }
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[MAIN_tk]);
      parseError();
    }
  } else {
    sprintf(expectedTks, "%s", TOKEN_NAMES[START_tk]);
    parseError();
  }

  return NULL; // Will not run
}

// <block> -> { <vars> <stats> }
Node* block () {
  Node *block_nd = createNode(BLOCK_nt);

  if (token.id == OPBRACE_tk) {
    token = scanner(inFile);

    addChild(block_nd, vars());
    addChild(block_nd, stats());

    if (token.id == CLBRACE_tk) {
      token = scanner(inFile);

      return block_nd; // Successful Parse
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[CLBRACE_tk]);
      parseError();
    }
  } else {
    sprintf(expectedTks, "%s", TOKEN_NAMES[OPBRACE_tk]);
    parseError();
  }

  return NULL; // Will not run
}

// <vars> -> empty | let Identifier : Integer <vars>
Node* vars () {
  Node *vars_nd = createNode(VARS_nt);

  if (token.id == LET_tk) {
    token = scanner(inFile);
    if (token.id == IDENT_tk) {
      addToken(vars_nd, token);

      token = scanner(inFile);
      if (token.id == COLON_tk) {
        addToken(vars_nd, token);

        token = scanner(inFile);
        if (token.id == NUM_tk) {
          addToken(vars_nd, token);

          token = scanner(inFile);

          addChild(vars_nd, vars());

          return vars_nd; // Successful parse
        } else {
          sprintf(expectedTks, "%s", TOKEN_NAMES[NUM_tk]);
          parseError();
        }
      } else {
        sprintf(expectedTks, "%s", TOKEN_NAMES[COLON_tk]);
        parseError();
      }
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[IDENT_tk]);
      parseError();
    }
  } else {
    free(vars_nd);
    return NULL; // Successful empty parse
  }

  return NULL; // Will not run
}

// <expr> -> <N> / <expr> | <N> * <expr> | <N>
// Separated into <expr_1> and <expr_2>

// <expr_1> -> <N> <expr_2>
Node* expr_1 () {
  Node *expr_nd = createNode(EXPR_nt);

  addChild(expr_nd, N_1());
  expr_2(expr_nd); // Continue parse in second function

  return expr_nd; // Successful parse
}

// <expr_2> -> / <expr_1> | * <expr_1> | empty
void expr_2 (Node *expr_nd) {
  if (token.id == DIV_tk) {
    addToken(expr_nd, token);

    token = scanner(inFile);

    addChild(expr_nd, expr_1());

    return;  // Successful parse
  } else if (token.id == MULT_tk) {
    addToken(expr_nd, token);

    token = scanner(inFile);

    addChild(expr_nd, expr_1());

    return; // Successful parse
  } else {
    return; // Successful empty parse
  }
}

// <N> -> <A> + <N> | <A> - <N> | <A>
// Separated into <N_1> and <N_2>

// <N_1> -> <A> <N_2>
Node* N_1 () {
  Node *N_nd = createNode(N_nt);

  addChild(N_nd, A());
  N_2(N_nd);

  return N_nd;
}

// <N_2> -> + <N_1> | - <N_1> | empty
void N_2 (Node *N_nd) {
  if (token.id == PLUS_tk) {
    addToken(N_nd, token);

    token = scanner(inFile);

    addChild(N_nd, N_1());

    return; // Successful parse
  } else if (token.id == MINUS_tk) {
    addToken(N_nd, token);

    token = scanner(inFile);

    addChild(N_nd, N_1());

    return; // Successful parse
  } else {
    return; // Successful empty parse
  }
}

// <A> -> % <A> | <R>
Node* A () {
  Node *A_nd = createNode(A_nt);

  if (token.id == MOD_tk) {
    addToken(A_nd, token);

    token = scanner(inFile);

    addChild(A_nd, A());

    return A_nd; // Successful parse
  } else {
    addChild(A_nd, R());

    return A_nd; // Successful parse
  }
}

// <R> -> [ <expr> ] | Identifier | Integer
Node* R () {
  Node *R_nd = createNode(R_nt);

  if (token.id == OPBRACK_tk) {
    token = scanner(inFile);

    addChild(R_nd, expr_1());

    if (token.id == CLBRACK_tk) {
      token = scanner(inFile);

      return R_nd; // Successful parse
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[CLBRACK_tk]);
      parseError();
    }
  } else if (token.id == IDENT_tk) {
    addToken(R_nd, token);

    token = scanner(inFile);

    return R_nd; // Successful parse
  } else if (token.id == NUM_tk) {
    addToken(R_nd, token);

    token = scanner(inFile);

    return R_nd; // Successful parse
  } else {
    sprintf(expectedTks, "%s, %s, or %s",
            TOKEN_NAMES[OPBRACK_tk], TOKEN_NAMES[IDENT_tk], TOKEN_NAMES[NUM_tk]);
    parseError();
  }

  return NULL; // Will not run
}

// <stats> -> <stat> <mStat>
Node* stats () {
  Node *stats_nd = createNode(STATS_nt);

  addChild(stats_nd, stat());
  addChild(stats_nd, mStat());

  return stats_nd;
}

// <mStat> -> empty | <stat> <mStat>
Node* mStat () {
  Node *mStat_nd = createNode(MSTAT_nt);

  // Test the first set of the production
  if ((token.id == SCANF_tk) || (token.id == PRINTF_tk) || (token.id == OPBRACE_tk)
      || (token.id == IF_tk) || (token.id == ITER_tk) || (token.id == IDENT_tk)) {
    addChild(mStat_nd, stat());
    addChild(mStat_nd, mStat());

    return mStat_nd; // Successful parse
  } else {
    free(mStat_nd);
    return NULL; // Successful empty parse
  }
}

// <stat> -> <in> . | <out> . | <block> | <if> . | <loop> . | <assign> .
Node* stat () {
  Node *stat_nd = createNode(STAT_nt);

  // Test the first set of each production
  if (token.id == SCANF_tk) {
    addChild(stat_nd, in());

    if (token.id == DOT_tk) {
      addToken(stat_nd, token);

      token = scanner(inFile);

      return stat_nd; // Successful parse
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[DOT_tk]);
      parseError();
    }
  } else if (token.id == PRINTF_tk) {
    addChild(stat_nd, out());

    if (token.id == DOT_tk) {
      addToken(stat_nd, token);

      token = scanner(inFile);

      return stat_nd; // Successful parse
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[DOT_tk]);
      parseError();
    }
  } else if (token.id == OPBRACE_tk) {
    addChild(stat_nd, block());

    return stat_nd; // Successful parse
  } else if (token.id == IF_tk) {
    addChild(stat_nd, if_par());

    if (token.id == DOT_tk) {
      addToken(stat_nd, token);

      token = scanner(inFile);

      return stat_nd; // Successful parse
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[DOT_tk]);
      parseError();
    }
  } else if (token.id == ITER_tk) {
    addChild(stat_nd, loop());

    if (token.id == DOT_tk) {
      addToken(stat_nd, token);

      token = scanner(inFile);

      return stat_nd; // Successful parse
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[DOT_tk]);
      parseError();
    }
  } else if (token.id == IDENT_tk) {
    addChild(stat_nd, assign());

    if (token.id == DOT_tk) {
      addToken(stat_nd, token);

      token = scanner(inFile);

      return stat_nd; // Successful parse
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[DOT_tk]);
      parseError();
    }
  } else {
    sprintf(expectedTks, "%s, %s, %s, %s, %s, or %s",
            TOKEN_NAMES[SCANF_tk], TOKEN_NAMES[PRINTF_tk], TOKEN_NAMES[OPBRACE_tk],
            TOKEN_NAMES[IF_tk], TOKEN_NAMES[ITER_tk], TOKEN_NAMES[IDENT_tk]);
    parseError();
  }

  return NULL; // Will not run
}

// <in> -> scanf [ Identifier ]
Node* in () {
  Node *in_nd = createNode(IN_nt);

  if (token.id == SCANF_tk) {
    token = scanner(inFile);
    if (token.id == OPBRACK_tk) {
      token = scanner(inFile);
      if (token.id == IDENT_tk) {
        addToken(in_nd, token);

        token = scanner(inFile);
        if (token.id == CLBRACK_tk) {
          token = scanner(inFile);

          return in_nd; // Successful parse
        } else {
          sprintf(expectedTks, "%s", TOKEN_NAMES[CLBRACK_tk]);
          parseError();
        }
      } else {
        sprintf(expectedTks, "%s", TOKEN_NAMES[IDENT_tk]);
        parseError();
      }
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[OPBRACK_tk]);
      parseError();
    }
  } else {
    sprintf(expectedTks, "%s", TOKEN_NAMES[SCANF_tk]);
    parseError();
  }

  return NULL; // Will not run
}

// <out> -> printf [ <expr> ]
Node* out () {
  Node *out_nd = createNode(OUT_nt);

  if (token.id == PRINTF_tk) {
    token = scanner(inFile);
    if (token.id == OPBRACK_tk) {
      token = scanner(inFile);

      addChild(out_nd, expr_1());

      if (token.id == CLBRACK_tk) {
        token = scanner(inFile);

        return out_nd; // Successful parse
      } else {
        sprintf(expectedTks, "%s", TOKEN_NAMES[CLBRACK_tk]);
        parseError();
      }
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[OPBRACK_tk]);
      parseError();
    }
  } else {
    sprintf(expectedTks, "%s", TOKEN_NAMES[PRINTF_tk]);
    parseError();
  }

  return NULL; // Will not run
}

// <if> -> if [ <expr> <RO> <expr> ] then <block>
Node* if_par () {
  Node *if_nd = createNode(IF_nt);

  if (token.id == IF_tk) {
    token = scanner(inFile);
    if (token.id == OPBRACK_tk) {
      token = scanner(inFile);

      addChild(if_nd, expr_1());
      addChild(if_nd, RO());
      addChild(if_nd, expr_1());

      if (token.id == CLBRACK_tk) {
        token = scanner(inFile);
        if (token.id == THEN_tk) {
          token = scanner(inFile);

          addChild(if_nd, block());

          return if_nd; // Successful parse
        } else {
          sprintf(expectedTks, "%s", TOKEN_NAMES[THEN_tk]);
          parseError();
        }
      } else {
        sprintf(expectedTks, "%s", TOKEN_NAMES[CLBRACK_tk]);
        parseError();
      }
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[OPBRACK_tk]);
      parseError();
    }
  } else {
    sprintf(expectedTks, "%s", TOKEN_NAMES[IF_tk]);
    parseError();
  }

  return NULL; // Will not run
}

// <loop> -> iter [ <expr> <RO> <expr> ] <block>
Node* loop () {
  Node *loop_nd = createNode(LOOP_nt);

  if (token.id == ITER_tk) {
    token = scanner(inFile);
    if (token.id == OPBRACK_tk) {
      token = scanner(inFile);

      addChild(loop_nd, expr_1());
      addChild(loop_nd, RO());
      addChild(loop_nd, expr_1());

      if (token.id == CLBRACK_tk) {
        token = scanner(inFile);

        addChild(loop_nd, block());

        return loop_nd; // Successful parse
      } else {
        sprintf(expectedTks, "%s", TOKEN_NAMES[CLBRACK_tk]);
        parseError();
      }
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[OPBRACK_tk]);
      parseError();
    }
  } else {
    sprintf(expectedTks, "%s", TOKEN_NAMES[ITER_tk]);
    parseError();
  }

  return NULL; // Will not run
}

// <assign> -> Identifier = <expr>
Node* assign () {
  Node *assign_nd = createNode(ASSIGN_nt);

  if (token.id == IDENT_tk) {
    addToken(assign_nd, token);

    token = scanner(inFile);
    if (token.id == ASSIGN_tk) {
      token = scanner(inFile);

      addChild(assign_nd, expr_1());

      return assign_nd; // Successful parse
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[ASSIGN_tk]);
      parseError();
    }
  } else {
    sprintf(expectedTks, "%s", TOKEN_NAMES[IDENT_tk]);
    parseError();
  }

  return NULL; // Will not run
}

// <RO> -> =< | => | == | : :
Node* RO () {
  Node *RO_nd = createNode(RO_nt);

  if (token.id == LTEQ_tk) {
    addToken(RO_nd, token);

    token = scanner(inFile);

    return RO_nd; // Successful parse
  } else if (token.id == GTEQ_tk) {
    addToken(RO_nd, token);

    token = scanner(inFile);

    return RO_nd; // Successful parse
  } else if (token.id == EQUAL_tk) {
    addToken(RO_nd, token);

    token = scanner(inFile);

    return RO_nd; // Successful parse
  } else if (token.id == COLON_tk) {
    addToken(RO_nd, token);

    token = scanner(inFile);
    if (token.id == COLON_tk) {
      addToken(RO_nd, token);

      token = scanner(inFile);

      return RO_nd; // Successful parse
    } else {
      sprintf(expectedTks, "%s", TOKEN_NAMES[COLON_tk]);
      parseError();
    }
  } else {
    sprintf(expectedTks, "%s, %s, %s, or %s", TOKEN_NAMES[LTEQ_tk],
            TOKEN_NAMES[GTEQ_tk], TOKEN_NAMES[EQUAL_tk], TOKEN_NAMES[COLON_tk]);
    parseError();
  }

  return NULL; // Will not run
}

/* Helper functions */

// Handles the error message for the parser
void parseError () {
  char errText[100];

  sprintf(errText, "Line %d - Received %s token instead of %s token(s).",
          token.lineNum, TOKEN_NAMES[token.id], expectedTks);

  errHandlerF(errText);
}
