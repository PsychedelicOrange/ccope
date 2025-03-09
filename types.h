#include "stringstruct.h"
#include "tokens.h"
#include <stddef.h>

// https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Functions.html
// ignoring volatile, inline,
// be carefull while parsing and make sure to not include function pointers
struct parameter {
  struct cursor cursor;
  int is_static;
  int is_const;
  struct TOKEN type; // must be a key word or a identifier ( unkown type ). if a
                     // struct/union/enum keyword was present, it will be
                     // ignored and the type tag will be stored here
  struct string name;
};

struct function_dec {
  struct cursor cursor;
  int is_static;
  struct TOKEN
      return_type; // must be a key word or a identifier ( unkown type ). if a
                   // struct/union/enum keyword was present, it will be ignored
                   // and the type tag will be stored here
  struct string name;
  size_t parameters_count;
  struct parameter parameters[100];
};

struct function_def {
  struct cursor cursor;
  struct function_dec declaration;
  struct TOKENS body;
};

// https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Enumeration-Types.html#Enumeration-Types
struct enum_def {
  struct cursor cursor;
  // name of enum
  struct string typetag;
  size_t enumerations_count;
  struct string enumerations[10000];
};

// https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Structures.html#Structures
// be carefull for bit fields when parsing

struct field {
  struct cursor cursor;
  int is_const;
  struct TOKEN type;
};

struct struct_def {
  struct cursor cursor;
  // name of struct
  struct string typetag;
  size_t fields_count;
  struct field fields[100];
};

struct union_def {
  struct cursor cursor;
  // name of union
  struct string typetag;
  size_t fields_count;
  struct field fields[100];
};

// https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Defining-Typedef-Names.html

struct typedef_def {
  struct cursor cursor;
  struct string typedef_name;
  struct string type;
};
