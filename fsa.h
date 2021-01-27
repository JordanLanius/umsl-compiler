#ifndef FSA_H
#define FSA_H

typedef enum {
  ERR = -1,

  S_1 = 0, S_2, S_3, S_4, S_5, S_6, S_7, S_8, S_9, S_10, S_11, S_12, S_13, S_14, S_15, S_16, S_17, S_18, S_19, S_20, S_21, S_22,

  FIN = 100
} State;

static const int FSA_TABLE[22][24] = {
  /* S_1  */ {ERR, S_2, S_3, S_4, ERR, ERR, S_8, S_9, S_10, S_11, S_12, S_13, S_14, S_15, S_16, S_17, S_18, S_19, S_20, S_21, S_22, S_1, S_1, FIN},
  /* S_2  */ {S_2, S_2, S_2, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_3  */ {ERR, ERR, S_3, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_4  */ {FIN, FIN, FIN, S_7, S_5, S_6, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_5  */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_6  */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_7  */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_8  */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_9  */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_10 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_11 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_12 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_13 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_14 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_15 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_16 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_17 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_18 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_19 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_20 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_21 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN},
  /* S_22 */ {FIN, FIN, FIN, FIN, FIN, FIN, FIN, FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN,  FIN, FIN, FIN, FIN}
};

#endif
