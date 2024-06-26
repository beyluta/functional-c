#ifndef FUNCTIONAL_TYPES
#define FUNCTIONAL_TYPES

#define new(type, size) (type *)malloc(size * sizeof(type))
#define iterator(type) type##_iterator
#define init_iterator(type, pArr, len) f_##type##_init(pArr, len)
#define destroy_iterator(type, iterator) f_##type##_destroy(iterator)

#define iterator_splice(type, iterator, from, to) \
    type *newArr = new (type, to - from);         \
    for (int i = from; i < to; i++)               \
    {                                             \
        newArr[i] = iterator.iterator[i];         \
    }                                             \
    return init_iterator(type, newArr, to - from);

#define iterator_map(type, func, iterator)               \
    type *new_iterator = new (type, iterator.len);       \
    for (int i = 0; i < iterator.len; i++)               \
    {                                                    \
        new_iterator[i] = func(iterator.iterator[i], i); \
    }                                                    \
    return init_iterator(type, new_iterator, iterator.len);

#define iterator_find(type, var, iterator) \
    for (int i = 0; i < iterator.len; i++) \
    {                                      \
        if (iterator.iterator[i] == var)   \
        {                                  \
            return var;                    \
        }                                  \
    }                                      \
    return 0;

#define iterator_some(type, var, iterator) \
    int some = 0;                          \
    for (int i = 0; i < iterator.len; i++) \
    {                                      \
        if (iterator.iterator[i] == var)   \
        {                                  \
            return 1;                      \
        }                                  \
    }                                      \
    return some;

#define iterator_every(type, var, iterator) \
    int every = 1;                          \
    for (int i = 0; i < iterator.len; i++)  \
    {                                       \
        if (iterator.iterator[i] != var)    \
        {                                   \
            return 0;                       \
        }                                   \
    }                                       \
    return every;

#define iterator_indexOf(type, var, iterator) \
    for (int i = 0; i < iterator.len; i++)    \
    {                                         \
        if (iterator.iterator[i] == var)      \
        {                                     \
            return i;                         \
        }                                     \
    }                                         \
    return -1;

#define iterator_sort(type, iterator, direction)                                                  \
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
    return new_struct_iterator;

#define iterator_filter(type, condition, var, iterator)                                                       \
    int size = 0;                                                                                             \
    for (int i = 0; i < iterator.len; i++)                                                                    \
    {                                                                                                         \
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var) \
        {                                                                                                     \
            size++;                                                                                           \
        }                                                                                                     \
    }                                                                                                         \
    type *pIterator = new (type, size);                                                                       \
    int index = 0;                                                                                            \
    for (int i = 0; i < iterator.len; i++)                                                                    \
    {                                                                                                         \
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var) \
        {                                                                                                     \
            pIterator[index++] = iterator.iterator[i];                                                        \
        }                                                                                                     \
    }                                                                                                         \
    return init_iterator(type, pIterator, size);

#endif