#include "stdio.h"
#include "stdlib.h"

#define POOL_SIZE 100
#define CUSTOM_TYPE char

struct Handle
{
    size_t index;
    size_t generation;
};

/* Pool implementation */
struct Pool
{
    CUSTOM_TYPE pool[POOL_SIZE];
    size_t generation[POOL_SIZE];
    size_t free[POOL_SIZE];
    size_t top;
};

struct Pool *initPool();

/* returns a Handle with a non-zero generation value in case of success */
struct Handle getHandle(struct Pool *pool, CUSTOM_TYPE value);

/* returns a null if handle is old */
CUSTOM_TYPE *getValue(struct Pool *pool, struct Handle handle);

void giveUpHandle(struct Pool *pool, struct Handle handle);
