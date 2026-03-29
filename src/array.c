#include "stdio.h"
#include "stdlib.h"

typedef void *any;

typedef enum
{
    floatt,
    doublet,
    intt,
    int8t,
    int16t,
    int32t,
    int64t,
    uintt,
    uint8t,
    uint16t,
    uint32t,
    uint64t
} basic_type;

size_t sizeoft(basic_type type)
{
    switch (type)
    {
    case intt:
        return sizeof(int);
    default:
        return -1;
    }
}

typedef struct
{
    size_t size;
    any *array;
    basic_type type;
} array;

static inline array make_array(basic_type type, size_t size)
{
    return (array){.size = size, .type = type, .array = malloc(sizeoft(type) * size)};
}

typedef int (*int_binary_int_int)(int a, int b);

int reduce(array a, int_binary_int_int op, any initial)
{
    int result = (int)initial;
    for (int i = 0; i < a.size; i++)
    {
        result = op(result, (int)a.array[i]);
    }
    return result;
}

int multiply(int a, int b)
{
    return a * b;
}

int main()
{
    array a = make_array(intt, 10);
    int reduction = reduce(a, multiply, (any)1);
    printf("%i", reduction);
    // same as
    int a_[10];
    int result = 1;
    for (int i = 0; i < 10; i++)
    {
        result *= a_[i];
    }
    printf("%i", result);
}
