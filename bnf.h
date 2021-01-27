#ifndef BNF_H
#define BNF_H

typedef enum {
  PROGRAM_nt, // <program>  ->  start <vars> main <block> stop
  BLOCK_nt,   // <block>  ->  { <vars> <stats> }
  VARS_nt,    // <vars>  ->  empty | let Identifier : Integer <vars>
  EXPR_nt,    // <expr>  ->  <N> / <expr> | <N> * <expr> | <N>
  N_nt,       // <N>  ->  <A> + <N> | <A> - <N> | <A>
  A_nt,       // <A>  ->  % <A> | <R>
  R_nt,       // <R>  ->  [ <expr> ] | Identifier | Integer
  STATS_nt,   // <stats>  ->  <stat> <mStat>
  MSTAT_nt,   // <mStat>  ->  empty | <stat> <mStat>
  STAT_nt,    // <stat>  ->  <in> . | <out> . | <block> | <if> . | <loop> . | <assign> .
  IN_nt,      // <in>  ->  scanf [ Identifier ]
  OUT_nt,     // <out>  ->  printf [ <expr> ]
  IF_nt,      // <if>  ->  if [ <expr> <RO> <expr> ] then <block>
  LOOP_nt,    // <loop>  ->  iter [ <expr> <RO> <expr> ] <block>
  ASSIGN_nt,  // <assign>  ->  Identifier = <expr>
  RO_nt       // <RO>  ->  =< | => | == | : :
} NonterminalID;

static const char NONTERM_NAMES[16][10] = {
  "<program>",
  "<block>",
  "<vars>",
  "<expr>",
  "<N>",
  "<A>",
  "<R>",
  "<stats>",
  "<mStat>",
  "<stat>",
  "<in>",
  "<out>",
  "<if>",
  "<loop>",
  "<assign>",
  "<RO>"
};

#endif
