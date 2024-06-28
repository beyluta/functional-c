#ifndef FUNCTIONAL
#define FUNCTIONAL

#include <stdlib.h>
#define new(type, size) (type *)malloc(size * sizeof(type))
#define array(type) type##_array
#define to_array(type, pArr, len) f_##type##_init(pArr, len)
#define destroy_array(type, array) f_##type##_destroy(array)
#define class_array(type)                                                                 \
    typedef struct type##_array                                                           \
    {                                                                                     \
        type *array;                                                                      \
        int len;                                                                          \
        struct type##_array (*map)(type(*func)(type, int), struct type##_array array);    \
        int (*find)(int (*func)(type, int), struct type##_array array);                   \
        int (*some)(int (*func)(type, int), struct type##_array array);                   \
        int (*every)(int (*func)(type, int), struct type##_array array);                  \
        int (*indexOf)(type var, struct type##_array array);                              \
        struct type##_array (*sort)(struct type##_array array, int direction);            \
        struct type##_array (*filter)(int (*func)(type, int), struct type##_array array); \
        struct type##_array (*slice)(int from, int to, struct type##_array array);        \
    } type##_array;                                                                       \
    struct type##_array f_##type##_init(type *arr, int len);                              \
    struct type##_array type##_map(type (*func)(type, int), struct type##_array array)    \
    {                                                                                     \
        type *new_array = new (type, array.len);                                          \
        for (int i = 0; i < array.len; i++)                                               \
        {                                                                                 \
            new_array[i] = func(array.array[i], i);                                       \
        }                                                                                 \
        return to_array(type, new_array, array.len);                                      \
    }                                                                                     \
    int type##_find(int (*func)(type, int), struct type##_array array)                    \
    {                                                                                     \
        for (int i = 0; i < array.len; i++)                                               \
        {                                                                                 \
            if (func(array.array[i], i))                                                  \
            {                                                                             \
                return 1;                                                                 \
            }                                                                             \
        }                                                                                 \
        return 0;                                                                         \
    }                                                                                     \
    int type##_some(int (*func)(type, int), struct type##_array array)                    \
    {                                                                                     \
        int some = 0;                                                                     \
        for (int i = 0; i < array.len; i++)                                               \
        {                                                                                 \
            if (func(array.array[i], i))                                                  \
            {                                                                             \
                return 1;                                                                 \
            }                                                                             \
        }                                                                                 \
        return some;                                                                      \
    }                                                                                     \
    int type##_every(int (*func)(type, int), struct type##_array array)                   \
    {                                                                                     \
        int every = 1;                                                                    \
        for (int i = 0; i < array.len; i++)                                               \
        {                                                                                 \
            if (!func(array.array[i], i))                                                 \
            {                                                                             \
                return 0;                                                                 \
            }                                                                             \
        }                                                                                 \
        return every;                                                                     \
    }                                                                                     \
    int type##_indexOf(type var, struct type##_array array)                               \
    {                                                                                     \
        for (int i = 0; i < array.len; i++)                                               \
        {                                                                                 \
            if (array.array[i] == var)                                                    \
            {                                                                             \
                return i;                                                                 \
            }                                                                             \
        }                                                                                 \
        return -1;                                                                        \
    }                                                                                     \
    struct type##_array type##_sort(struct type##_array array, int direction)             \
    {                                                                                     \
        type *new_array = new (type, array.len);                                          \
        for (int i = 0; i < array.len; i++)                                               \
        {                                                                                 \
            new_array[i] = array.array[i];                                                \
        }                                                                                 \
        struct type##_array new_struct_array = to_array(type, new_array, array.len);      \
                                                                                          \
        for (int i = 0; i < new_struct_array.len; i++)                                    \
        {                                                                                 \
            if (direction)                                                                \
            {                                                                             \
                for (int j = 0; j < new_struct_array.len; j++)                            \
                {                                                                         \
                    if (i != j && new_struct_array.array[i] < new_struct_array.array[j])  \
                    {                                                                     \
                        type temp = new_struct_array.array[i];                            \
                        new_struct_array.array[i] = new_struct_array.array[j];            \
                        new_struct_array.array[j] = temp;                                 \
                    }                                                                     \
                }                                                                         \
            }                                                                             \
            else                                                                          \
            {                                                                             \
                for (int j = 0; j < new_struct_array.len; j++)                            \
                {                                                                         \
                    if (i != j && new_struct_array.array[i] > new_struct_array.array[j])  \
                    {                                                                     \
                        type temp = new_struct_array.array[i];                            \
                        new_struct_array.array[i] = new_struct_array.array[j];            \
                        new_struct_array.array[j] = temp;                                 \
                    }                                                                     \
                }                                                                         \
            }                                                                             \
        }                                                                                 \
        return new_struct_array;                                                          \
    }                                                                                     \
    struct type##_array type##_filter(int (*func)(type, int), struct type##_array array)  \
    {                                                                                     \
        int len = 0;                                                                      \
        for (int i = 0; i < array.len; i++)                                               \
        {                                                                                 \
            if (func(array.array[i], i))                                                  \
            {                                                                             \
                len++;                                                                    \
            }                                                                             \
        }                                                                                 \
        type *newArr = new (type, len);                                                   \
        int index = 0;                                                                    \
        for (int i = 0; i < array.len; i++)                                               \
        {                                                                                 \
            if (func(array.array[i], i))                                                  \
            {                                                                             \
                newArr[index++] = array.array[i];                                         \
            }                                                                             \
        }                                                                                 \
        return to_array(type, newArr, len);                                               \
    }                                                                                     \
    struct type##_array type##_slice(int from, int to, struct type##_array array)         \
    {                                                                                     \
        type *newArr = new (type, to - from);                                             \
        for (int i = from; i < to; i++)                                                   \
        {                                                                                 \
            newArr[i] = array.array[i];                                                   \
        }                                                                                 \
        return to_array(type, newArr, to - from);                                         \
    }                                                                                     \
    struct type##_array f_##type##_init(type *arr, int len)                               \
    {                                                                                     \
        struct type##_array array = {                                                     \
            array.array = arr,                                                            \
            array.len = len,                                                              \
            array.map = type##_map,                                                       \
            array.find = type##_find,                                                     \
            array.some = type##_some,                                                     \
            array.every = type##_every,                                                   \
            array.indexOf = type##_indexOf,                                               \
            array.sort = type##_sort,                                                     \
            array.filter = type##_filter,                                                 \
            array.slice = type##_slice};                                                  \
        return array;                                                                     \
    }                                                                                     \
    void f_##type##_destroy(struct type##_array array)                                    \
    {                                                                                     \
        if (array.array != NULL)                                                          \
        {                                                                                 \
            free(array.array);                                                            \
        }                                                                                 \
    }

class_array(int);
class_array(short);
class_array(float);
class_array(double);
class_array(long);
class_array(char);

#endif