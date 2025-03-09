#include "hashmap.h"
#include "lexer.h"
#include "log.h"
#include "tokens.h"

struct Hashmap hashmap;
void print_tokens(struct TOKENS tokens) {
  for (int i = 0; i < tokens.index; i++) {
    if (tokens.array[i].tokentype == SYMBOL) {
      char c = tokens.array[i].utoken.single_token;
      switch (c) {
      case GTE:
        logp(">=");
        break;
      case LTE:
        logp(">=");
        break;
      case EQ:
        logp(">=");
        break;
      case NEW_LINE:
        logp("\n");
        break;
      default:
        logp("%c", tokens.array[i].utoken.single_token);
      }
    } else if (tokens.array[i].tokentype == KEYWORD)
      logp("%s",
           hash_getString(hashmap, tokens.array[i].utoken.multi_token).array);
    else
      logp("%s", tokens.array[i].utoken.identifier.iden_string);
    logp(" ");
  }
}
int main(int argv, char *args[]) {
  if (argv <= 1) {
    loge("No file provided.");
    exit(-1);
  }
  hash_init(&hashmap, 10000);
  hash_insert_all_tokens(&hashmap);

  FILE *file = fopen(args[1], "r");
  struct TOKENS tokens = lex(file);
  print_tokens(tokens);
}
