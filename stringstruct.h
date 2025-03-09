#ifndef STRING_STRUCT_H
#define STRING_STRUCT_H
#include <stdio.h>
#include <stdlib.h>
struct string {
  char *array;
  size_t size;
};
// create a new string obj and malloc size to it
struct string string_malloc(size_t size);
// free memory taken by string
void string_free(struct string str);
// print non-null terminated string
void string_print(struct string str);
// make and return a deep copy of the string
struct string string_copy(struct string src);
// make and return a deep copy of the string
struct string string_copy_null_terminated_string(char *src);
// make and return a deep copy of the string
struct string string_copy_c_style(char *src, size_t size);
// compare two string objects
int string_compare(struct string a, struct string b);
// compare string object with a c style string
int string_compare_c_style(struct string a, char *b);
// create a new string
struct string string_cat(struct string src, const char *append);

// WIP
char *substring_replace(const char *string, const char *substring,
                        const char *replacementTerm);
#endif
