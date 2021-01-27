/*
 * Compiler Project
 * UMSL - CS 4280
 * December 10, 2020
 * Jordan Lanius - jordan.lanius@gmail.com
 *
 * - scanner.c -
 * This file contains a token scanner that converts character input into tokens.
 * Function initializeScanner must be called before using the scanner.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "errhandler.h"
#include "fsa.h"
#include "token.h"

Character filter (FILE*);

Character lookahead; // Next character
int lineNum = 1;

// Reads the first character for the scanner to use
void initializeScanner (FILE* inFile) {
  lookahead = filter(inFile);
}

// Read characters until a token is found.
// Uses a FSA table to determine which token is found.
Token scanner (FILE* inFile) {
  State presentState = S_1;
  State nextState;
  Token scanToken;
  char scanInstance[10] = "";

  // Loop until a token is found in the FSA table
  while (presentState != FIN) {
    nextState = FSA_TABLE[presentState][lookahead.id];

    if (nextState == ERR) {
      errHandlerF("Input does not match language.");
    } else if (nextState == FIN) {
      scanToken.id = (TokenID) presentState;
      scanToken.lineNum = lookahead.lineNum;

      // If identifier is a keyword, swap tokenID
      if (scanToken.id == IDENT_tk) {
        int index;
        for (index = 0; index < NUM_KEYWORD_TK; index++) {
          if (strcmp(KEYWORDS[index], scanInstance) == 0) {
            scanToken.id = (TokenID) (index + NUM_BASIC_TK);
          }
        }
      }

      // Add instance if many-to-one (Identifier or Integer)
      if ((scanToken.id == IDENT_tk) || (scanToken.id == NUM_tk)) {
        strcpy(scanToken.instance, scanInstance);
      } else {
        strcpy(scanToken.instance, "");
      }

      presentState = nextState;
    } else {
      // Ignore whitespace and comments when constructing potential instance
      if ((lookahead.id != WS_ch) && (lookahead.id != COMMENT_ch)) {
        int length = strlen(scanInstance);
        scanInstance[length] = lookahead.instance;
        scanInstance[length + 1] = '\0';
      }

      presentState = nextState;
      lookahead = filter(inFile); // Read new lookahead character
    }
  }

  return scanToken;
}

// Filter out comment text and keep track of line number
Character filter (FILE* inFile) {
  Character filtChar;
  char tempInst = fgetc(inFile);
  CharacterID tempID = getCharID(tempInst);

  // Remove comment text
  if (tempID == COMMENT_ch) {
    do {
      tempInst = fgetc(inFile);
    } while (tempInst != '\n');

    filtChar.id = tempID;
    filtChar.instance = '#';
    filtChar.lineNum = lineNum;

    lineNum++;
  } else if ((tempID >= UPPER_ch) && (tempID <= EOF_ch)) {
    filtChar.id = tempID;
    filtChar.instance = tempInst;
    filtChar.lineNum = lineNum;

    if (tempInst == '\n') {
      lineNum++;
    }
  } else {
    errHandlerF("Character not found in alphabet.");
  }

  return filtChar;
}
