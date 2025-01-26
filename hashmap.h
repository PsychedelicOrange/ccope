#ifndef HASHMAP_PSYCH_H
#define HASHMAP_PSYCH_H

#include "stringstruct.h"
#include "tokens.h"
#include <stddef.h>

struct KEYWORD_ENTRY {
  enum KEYWORD token; // 4 bytes
  struct string str;
};
struct Hashmap {
  struct KEYWORD_ENTRY *hash;
  struct KEYWORD_ENTRY *array;
  size_t size;
};
// functions forward declaration
void hash_init(struct Hashmap *hashmap, size_t size);
int hash_insert(struct Hashmap *hashmap, enum KEYWORD token, char *word,
                size_t size);
int hash_contains(struct Hashmap *hashmap, char *word, size_t size);
int hash_getToken(struct Hashmap *hashmap, char *word, size_t size);
void hash_insert_all_tokens(struct Hashmap *hashmap);
struct string hash_getString(struct Hashmap hashmap, enum KEYWORD mtoken);

#endif
