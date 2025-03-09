#include "annotation.h"

struct modifications ToString(const struct annotation a,
                              struct annotation_context ctx) {
  if (ctx.types.a_enum) {
    size_t count = ctx.enum_def.enumerations_count;

    sds text = sdscatfmt(sdsempty(), "struct string %stoString(enum %s field){ \
			switch(field){ ",
                         ctx.enum_def.typetag, ctx.enum_def.typetag);

    sds tail = sdsnew("};\
		};");

    for (int i = 0; i < count; i++) {
      text =
          sdscatfmt(text, "\ncase %s:\
				return %s;\
				break;",
                    ctx.enum_def.enumerations[i], ctx.enum_def.enumerations[i]);
    };
    text = sdscat(text, tail);

    struct modification mod = {
        .text = text, .mode = INSERT, .location_at = ctx.after_type};
    struct modifications mods;
    mods.mods = malloc(sizeof(struct modification));
    mods.mods[0] = mod;
    mods.mods_count = 1;
    return mods;
  } else {
    // error - only enums can be annotated with annotations
  }
  return (struct modifications){.mods_count = 0};
};

struct annotation annotation() {
  return (struct annotation){.name =
                                 string_copy_null_terminated_string("ToString"),
                             .types = {.a_enum = 1},
                             .definition = ToString};
}
