#include "pool.h"

/* Return a malloc-ed pool */
struct Pool *initPool()
{
    struct Pool *pool = malloc(sizeof(struct Pool));
    pool->top = POOL_SIZE - 1;
    for (size_t i = 0; i < POOL_SIZE; i++)
    {
        pool->generation[i] = 1;
        pool->free[POOL_SIZE - 1 - i] = i;
    }
    return pool;
}

/* returns a Handle with a non-zero generation value in case of success */
struct Handle getHandle(struct Pool *pool, CUSTOM_TYPE value)
{
    if (pool->top == 0)
    {
        return (struct Handle){.generation = 0};
    }
    else
    {
        int free_index = pool->free[pool->top--];
        pool->pool[free_index] = value;
        return (struct Handle){.generation = pool->generation[free_index], .index = free_index};
    }
};

/* returns a null if handle is old */
CUSTOM_TYPE *getValue(struct Pool *pool, struct Handle handle)
{
    if (handle.generation == pool->generation[handle.index])
    {
        return &(pool->pool[handle.index]);
    }
    return NULL;
};

void giveUpHandle(struct Pool *pool, struct Handle handle)
{
    if (handle.generation != pool->generation[handle.index])
    {
        printf("\nERROR: can't give up Handle as handle is stale! ");
        return;
    }
    if (pool->top == 99)
    {
        printf("\nERROR: can't give up Handle as stack is already full! ");
    }
    else
    {
        int free_index = ++pool->top;
        pool->free[free_index] = handle.index;
        pool->generation[handle.index]++;
    }
};
