#include "hashmap.h"
#include "log.h"
#include "tokens.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void hash_init(struct Hashmap *hashmap, size_t size) {
  assert(hashmap != NULL);
  hashmap->hash = malloc(size * sizeof(struct KEYWORD_ENTRY));
  hashmap->size = size;
  for (size_t i = 0; i < hashmap->size; i++) {
    hashmap->hash[i].token = NULL_DEBUG;
    hashmap->hash[i].str.array = NULL;
    hashmap->hash[i].str.size = 0;
  }
}
int hash_insert(struct Hashmap *hashmap, enum KEYWORD token, char *word,
                size_t size) {
  int sum = 0;
  for (size_t i = 0; i < size; i++) {
    sum += word[i];
  }
  //	fprintf(stderr,"while inserting %s... hashIndex is %i\n",word,sum);
  int hashindex = sum % hashmap->size;
  assert(hashindex < hashmap->size);
  if (hashmap->hash[hashindex].token == NULL_DEBUG) {
    hashmap->hash[hashindex].str = string_copy_c_style(word, size);
    hashmap->hash[hashindex].token = token;
    return 1;
  } else if (hashmap->hash[hashindex].token != token) { // collision
    hashindex++;
    while (hashindex < hashmap->size) {
      if (hashmap->hash[hashindex].token == NULL_DEBUG) {
        hashmap->hash[hashindex].str = string_copy_c_style(word, size);
        hashmap->hash[hashindex].token = token;
        return 1;
      } else if (hashmap->hash[hashindex].token == token) {
        return 0;
      }
    }
    return 0;
  }
  return 0;
}
int hash_contains(struct Hashmap *hashmap, char *word, size_t size) {
  int sum = 0;
  for (size_t i = 0; i < size; i++) {
    logp("%c", word[i]);
    sum += word[i];
  }
  int hashindex = sum % hashmap->size;
  while (hashindex < hashmap->size) {
    if (size == hashmap->hash[hashindex].str.size &&
        !strncmp(hashmap->hash[hashindex].str.array, word, size)) {
      return 1;
    } else if (hashmap->hash[hashindex].token == NULL_DEBUG) {
      return 0;
    } else {
      hashindex++;
    }
  }
  return 0;
}
struct string hash_getString(struct Hashmap hashmap, enum KEYWORD mtoken) {
  for (size_t i = 0; i < hashmap.size; i++) {
    if (hashmap.hash[i].token == mtoken) {
      return hashmap.hash[i].str;
    }
  }
  struct string str;
  str.size = 0;
  str.array = NULL;
  return str;
}
int hash_getToken(struct Hashmap *hashmap, char *word, size_t size) {
  // string_print(string_copy_c_style(word,size));
  int sum = 0;
  for (size_t i = 0; i < size; i++) {
    sum += word[i];
  }
  int hashindex = sum % hashmap->size;
  // printf(";	hash_index:%i",hashindex);
  while (hashindex < hashmap->size) {
    if (size == hashmap->hash[hashindex].str.size &&
        !strncmp(hashmap->hash[hashindex].str.array, word, size)) {
      return hashmap->hash[hashindex].token;
    } else if (hashmap->hash[hashindex].token == NULL_DEBUG) {
      return hashmap->hash[hashindex].token;
    } else {
      hashindex++;
    }
  }
  return NULL_DEBUG;
}
void hash_insert_all_tokens(struct Hashmap *hashmap) {
  hash_insert(hashmap, IF, "if\0", 2);
  hash_insert(hashmap, FOR, "for\0", 3);
  hash_insert(hashmap, INT, "int\0", 3);
  hash_insert(hashmap, ELSE, "else\0", 4);
  hash_insert(hashmap, LONG, "long\0", 4);
  hash_insert(hashmap, ENUM, "enum\0", 4);
  hash_insert(hashmap, CASE, "case\0", 4);
  hash_insert(hashmap, CHAR, "char\0", 4);
  hash_insert(hashmap, WHILE, "while\0", 5);
  hash_insert(hashmap, UNION, "union\0", 5);
  hash_insert(hashmap, FLOAT, "float\0", 5);
  hash_insert(hashmap, SHORT, "short\0", 5);
  hash_insert(hashmap, CONST, "const\0", 5);
  hash_insert(hashmap, SWITCH, "switch\0", 6);
  hash_insert(hashmap, EXTERN, "extern\0", 6);
  hash_insert(hashmap, RETURN, "return\0", 6);
  hash_insert(hashmap, SIGNED, "signed\0", 6);
  hash_insert(hashmap, SIZEOF, "sizeof\0", 6);
  hash_insert(hashmap, STATIC, "static\0", 6);
  hash_insert(hashmap, STRUCT, "struct\0", 6);
  hash_insert(hashmap, DOUBLE, "double\0", 6);
  hash_insert(hashmap, TYPEDEF, "typedef\0", 7);
  hash_insert(hashmap, DEFAULT, "default\0", 7);
  hash_insert(hashmap, UNSIGNED, "unsigned\0", 8);
  hash_insert(hashmap, CONTINUE, "continue\0", 8);
}
