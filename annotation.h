#include "sds.h"
#include "stringstruct.h"
#include "types.h"

struct annotation;
struct annotation_context;
struct annotation_types {
  unsigned int a_function : 1;
  unsigned int a_parameter : 1;
  unsigned int a_file : 1;
  unsigned int a_struct : 1;
  unsigned int a_struct_field : 1;
  unsigned int a_enum : 1;
  unsigned int a_enum_field : 1;
  unsigned int a_union : 1;
  unsigned int a_union_field : 1;
};

enum modification_mode {
  INSERT,
  REPLACE,
};

struct modification {
  struct string text;
  enum modification_mode mode;
  struct cursor location_at;
};

struct modifications {
  struct modification *mods;
  size_t mods_count;
};

struct annotation_context {
  struct annotation_types types;
  struct function_def function_def;
  struct enum_def enum_def;
  struct struct_def struct_def;
  struct union_def union_def;
  struct cursor beginning_of_file;
  struct cursor before_type;
  struct cursor after_type;
  struct cursor end_of_file;
};

typedef struct modifications (*define_annotation)(
    struct annotation a, struct annotation_context ctx);

struct annotation {
  struct string name;
  struct annotation_types types;
  define_annotation definition;
};
