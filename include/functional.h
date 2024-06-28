#ifndef FUNCTIONAL
#define FUNCTIONAL

#include <stdlib.h>
#define new(type, size) (type *)malloc(size * sizeof(type))
#define iterator(type) type##_iterator
#define init_iterator(type, pArr, len) f_##type##_init(pArr, len)
#define destroy_iterator(type, iterator) f_##type##_destroy(iterator)
#define class_iterator(type)                                                                          \
    typedef struct type##_iterator                                                                    \
    {                                                                                                 \
        type *iterator;                                                                               \
        int len;                                                                                      \
        struct type##_iterator (*map)(type(*func)(type, int), struct type##_iterator iterator);       \
        int (*find)(int (*func)(type, int), struct type##_iterator iterator);                         \
        int (*some)(type var, struct type##_iterator iterator);                                       \
        int (*every)(type var, struct type##_iterator iterator);                                      \
        int (*indexOf)(type var, struct type##_iterator iterator);                                    \
        struct type##_iterator (*sort)(struct type##_iterator iterator, int direction);               \
        struct type##_iterator (*filter)(int (*func)(type, int), struct type##_iterator iterator);    \
        struct type##_iterator (*splice)(int from, int to, struct type##_iterator iterator);          \
    } type##_iterator;                                                                                \
    struct type##_iterator f_##type##_init(type *arr, int len);                                       \
    struct type##_iterator type##_map(type (*func)(type, int), struct type##_iterator iterator)       \
    {                                                                                                 \
        type *new_iterator = new (type, iterator.len);                                                \
        for (int i = 0; i < iterator.len; i++)                                                        \
        {                                                                                             \
            new_iterator[i] = func(iterator.iterator[i], i);                                          \
        }                                                                                             \
        return init_iterator(type, new_iterator, iterator.len);                                       \
    }                                                                                                 \
    int type##_find(int (*func)(type, int), struct type##_iterator iterator)                          \
    {                                                                                                 \
        for (int i = 0; i < iterator.len; i++)                                                        \
        {                                                                                             \
            if (func(iterator.iterator[i], i))                                                        \
            {                                                                                         \
                return 1;                                                                             \
            }                                                                                         \
        }                                                                                             \
        return 0;                                                                                     \
    }                                                                                                 \
    int type##_some(type var, struct type##_iterator iterator)                                        \
    {                                                                                                 \
        int some = 0;                                                                                 \
        for (int i = 0; i < iterator.len; i++)                                                        \
        {                                                                                             \
            if (iterator.iterator[i] == var)                                                          \
            {                                                                                         \
                return 1;                                                                             \
            }                                                                                         \
        }                                                                                             \
        return some;                                                                                  \
    }                                                                                                 \
    int type##_every(type var, struct type##_iterator iterator)                                       \
    {                                                                                                 \
        int every = 1;                                                                                \
        for (int i = 0; i < iterator.len; i++)                                                        \
        {                                                                                             \
            if (iterator.iterator[i] != var)                                                          \
            {                                                                                         \
                return 0;                                                                             \
            }                                                                                         \
        }                                                                                             \
        return every;                                                                                 \
    }                                                                                                 \
    int type##_indexOf(type var, struct type##_iterator iterator)                                     \
    {                                                                                                 \
        for (int i = 0; i < iterator.len; i++)                                                        \
        {                                                                                             \
            if (iterator.iterator[i] == var)                                                          \
            {                                                                                         \
                return i;                                                                             \
            }                                                                                         \
        }                                                                                             \
        return -1;                                                                                    \
    }                                                                                                 \
    struct type##_iterator type##_sort(struct type##_iterator iterator, int direction)                \
    {                                                                                                 \
        type *new_iterator = new (type, iterator.len);                                                \
        for (int i = 0; i < iterator.len; i++)                                                        \
        {                                                                                             \
            new_iterator[i] = iterator.iterator[i];                                                   \
        }                                                                                             \
        struct type##_iterator new_struct_iterator = init_iterator(type, new_iterator, iterator.len); \
                                                                                                      \
        for (int i = 0; i < new_struct_iterator.len; i++)                                             \
        {                                                                                             \
            if (direction)                                                                            \
            {                                                                                         \
                for (int j = 0; j < new_struct_iterator.len; j++)                                     \
                {                                                                                     \
                    if (i != j && new_struct_iterator.iterator[i] < new_struct_iterator.iterator[j])  \
                    {                                                                                 \
                        type temp = new_struct_iterator.iterator[i];                                  \
                        new_struct_iterator.iterator[i] = new_struct_iterator.iterator[j];            \
                        new_struct_iterator.iterator[j] = temp;                                       \
                    }                                                                                 \
                }                                                                                     \
            }                                                                                         \
            else                                                                                      \
            {                                                                                         \
                for (int j = 0; j < new_struct_iterator.len; j++)                                     \
                {                                                                                     \
                    if (i != j && new_struct_iterator.iterator[i] > new_struct_iterator.iterator[j])  \
                    {                                                                                 \
                        type temp = new_struct_iterator.iterator[i];                                  \
                        new_struct_iterator.iterator[i] = new_struct_iterator.iterator[j];            \
                        new_struct_iterator.iterator[j] = temp;                                       \
                    }                                                                                 \
                }                                                                                     \
            }                                                                                         \
        }                                                                                             \
        return new_struct_iterator;                                                                   \
    }                                                                                                 \
    struct type##_iterator type##_filter(int (*func)(type, int), struct type##_iterator iterator)     \
    {                                                                                                 \
        int len = 0;                                                                                  \
        for (int i = 0; i < iterator.len; i++)                                                        \
        {                                                                                             \
            if (func(iterator.iterator[i], i))                                                        \
            {                                                                                         \
                len++;                                                                                \
            }                                                                                         \
        }                                                                                             \
        type *newArr = new (type, len);                                                               \
        int index = 0;                                                                                \
        for (int i = 0; i < iterator.len; i++)                                                        \
        {                                                                                             \
            if (func(iterator.iterator[i], i))                                                        \
            {                                                                                         \
                newArr[index++] = iterator.iterator[i];                                               \
            }                                                                                         \
        }                                                                                             \
        return init_iterator(type, newArr, len);                                                      \
    }                                                                                                 \
    struct type##_iterator type##_splice(int from, int to, struct type##_iterator iterator)           \
    {                                                                                                 \
        type *newArr = new (type, to - from);                                                         \
        for (int i = from; i < to; i++)                                                               \
        {                                                                                             \
            newArr[i] = iterator.iterator[i];                                                         \
        }                                                                                             \
        return init_iterator(type, newArr, to - from);                                                \
    }                                                                                                 \
    struct type##_iterator f_##type##_init(type *arr, int len)                                        \
    {                                                                                                 \
        struct type##_iterator iterator = {                                                           \
            iterator.iterator = arr,                                                                  \
            iterator.len = len,                                                                       \
            iterator.map = type##_map,                                                                \
            iterator.find = type##_find,                                                              \
            iterator.some = type##_some,                                                              \
            iterator.every = type##_every,                                                            \
            iterator.indexOf = type##_indexOf,                                                        \
            iterator.sort = type##_sort,                                                              \
            iterator.filter = type##_filter,                                                          \
            iterator.splice = type##_splice};                                                         \
        return iterator;                                                                              \
    }                                                                                                 \
    void f_##type##_destroy(struct type##_iterator iterator)                                          \
    {                                                                                                 \
        if (iterator.iterator != NULL)                                                                \
        {                                                                                             \
            free(iterator.iterator);                                                                  \
        }                                                                                             \
    }

class_iterator(int);
class_iterator(short);
class_iterator(float);
class_iterator(double);
class_iterator(long);
class_iterator(char);

#endif