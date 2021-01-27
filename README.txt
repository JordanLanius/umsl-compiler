Compiler Project
UMSL - CS 4280

Date: December 14, 2020
Author: Jordan Lanius
        jordan.lanius@gmail.com


---------- ABOUT ----------
> Translates from .fs to .asm

> Utilizes a FSA table and driver.
  > FSA table is in fsa.h
  > Driver is the function scanner(FILE*) in scanner.c

> Static semantics can handle local scopes.


---------- USAGE ----------
make          : Compiles frontEnd executable
make clean    : Removes executable and *.o files from directory
make cleanout : Removes .asm files from the directory

./compfs
  > Reads input from keyboard
  > Outputs generated code to kb.asm

./compfs filename
  > Reads input from filename.fs
  > Outputs generated code to filename.asm

./compfs < filename
  > Reads input from filename
  > Outputs generated code to kb.asm
