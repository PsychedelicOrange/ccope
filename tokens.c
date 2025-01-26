#include "tokens.h"
#include "log.h"

void tokens_init(struct TOKENS *tokens, size_t size) {
  tokens->size = size;
  tokens->index = 0;
  tokens->array = malloc(size * sizeof(struct TOKEN));
}

void tokens_add_singletoken(struct TOKENS *tokens, enum SYMBOL singletoken) {
  struct TOKEN token;
  token.utoken.single_token = singletoken;
  token.tokentype = SYMBOL;
  tokens->array[(tokens->index)++] = token;
}

int tokens_is_singletoken(struct TOKEN token, enum SYMBOL c) {
  return token.tokentype == SYMBOL && token.utoken.single_token == c;
}
