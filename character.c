/*
 * Compiler Project
 * UMSL - CS 4280
 * December 10, 2020
 * Jordan Lanius - jordan.lanius@gmail.com
 *
 * - character.c -
 * This file contains the characterID function that determines what kind of
 * character is sent as an argument.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "character.h"

// Returns the characterID associated with the character argument
CharacterID getCharID (char inChar) {
  if (isspace(inChar)) {
    return WS_ch;
  } else if (isupper(inChar)) {
    return UPPER_ch;
  } else if (islower(inChar)) {
    return LOWER_ch;
  } else if (isdigit(inChar)) {
    return DIGIT_ch;
  } else {
    switch (inChar) {
      case '=':
        return EQUAL_ch;
      case '>':
        return GREATER_ch;
      case '<':
        return LESS_ch;
      case ':':
        return COLON_ch;
      case '+':
        return PLUS_ch;
      case '-':
        return MINUS_ch;
      case '*':
        return MULT_ch;
      case '/':
        return DIV_ch;
      case '%':
        return MOD_ch;
      case '.':
        return DOT_ch;
      case '(':
        return OPPAREN_ch;
      case ')':
        return CLPAREN_ch;
      case ',':
        return COMMA_ch;
      case '{':
        return OPBRACE_ch;
      case '}':
        return CLBRACE_ch;
      case ';':
        return SEMICOL_ch;
      case '[':
        return OPBRACK_ch;
      case ']':
        return CLBRACK_ch;
      case '#':
        return COMMENT_ch;
      case EOF:
        return EOF_ch;
      default:
        return -1;
    }
  }
}
