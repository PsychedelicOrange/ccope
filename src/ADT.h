// or type (union) with helper functions

struct Either {
  union {
    type1 left;
    type2 right;
  };
  unsigned int isLeft;
};
