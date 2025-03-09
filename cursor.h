#include "stdio.h"

struct cursor {
  /* lexer responsibility to fill these per token */
  char file[256];
  size_t scope;
  size_t line;
  size_t loc;
};
