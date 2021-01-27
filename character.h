#ifndef CHARACTER_H
#define CHARACTER_H

typedef enum {
  // Alphanumeric
  UPPER_ch, LOWER_ch, DIGIT_ch,

  // Operator Characters
  EQUAL_ch, GREATER_ch, LESS_ch, COLON_ch,
  PLUS_ch, MINUS_ch, MULT_ch, DIV_ch, MOD_ch, DOT_ch,

  // Delimiter Characters
  OPPAREN_ch, CLPAREN_ch, COMMA_ch, OPBRACE_ch, CLBRACE_ch,
  SEMICOL_ch, OPBRACK_ch, CLBRACK_ch,

  // Other
  WS_ch, COMMENT_ch, EOF_ch
} CharacterID;

typedef struct character_struct {
  CharacterID id;
  char instance;
  int lineNum;
} Character;

static const char specialChars[18] = "=><:+-*/%.(),{};[]";

CharacterID getCharID (char);

#endif
