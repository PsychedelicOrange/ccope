#include "stringstruct.h"
#include <string.h>

struct string string_malloc(size_t size) {
  struct string str;
  str.array = malloc(size);
  str.size = size;
  return str;
}
void string_free(struct string str) { free(str.array); }

void string_print(struct string str) {
  fwrite(str.array, sizeof(char), str.size, stdout);
  printf("\n");
}

struct string string_cpy(struct string dst, struct string src) {
  if (dst.size < src.size) {
    printf("[ERROR] Can't copy as size of dst < src");
  };
  memcpy(dst.array, src.array, src.size);
  return dst;
}

struct string string_copy_null_terminated_string(char *src) {
  return string_copy_c_style(src, strlen(src));
}
// cstyle string are the ones which are null terminated, might wanna rename this
struct string string_copy_c_style(char *src, size_t size) {
  struct string str = string_malloc(size);
  memcpy(str.array, src, size);
  str.size = size;
  return str;
}

int string_compare(struct string a, struct string b) {
  return strncmp(a.array, b.array, a.size < b.size ? a.size : b.size);
}
int string_compare_c_style(struct string a, char *b) {
  return strncmp(a.array, b, a.size);
}

struct string string_cat(struct string src, const char *append) {
  struct string result = string_malloc(src.size + strlen(append));
  strncpy(result.array, src.array, src.size);
  strncpy(result.array + src.size, append, strlen(append));
  string_free(src);
  return result;
};

/* creates a new string with a null terminator */
char *get_null_terminated(struct string s) {
  struct string s_n = string_malloc(s.size + 1);
  string_cpy(s_n, s);
  s_n.array[s_n.size - 1] = '\0';
  return s_n.array;
}
