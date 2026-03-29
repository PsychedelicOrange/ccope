#include "pool.h"

struct Pool *alphabets;

int main()
{
    alphabets = initPool();

    struct Handle A = getHandle(alphabets, 'A');
    if (A.generation == 0)
    {
        printf("Pool is full!");
    }

    char *val = getValue(alphabets, A);
    if (val == NULL)
    {
        printf("Invalid handle!");
    }
    else
    {
        printf("Value of Handle A is %c", *val);
    }

    giveUpHandle(alphabets, A);

    free(alphabets);
};
