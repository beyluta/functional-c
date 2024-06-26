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

#endif