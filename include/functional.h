#ifndef FUNCTIONAL
#define FUNCTIONAL

#include <stdlib.h>

#define new(type, size) (type *)malloc(size * sizeof(type))
#define iterator(type) type##_iterator
#define init_iterator(type, pArr, len) f_##type##_init(pArr, len)
#define destroy_iterator(type, iterator) f_##type##_destroy(iterator)

#define def_iterator_struct(type)                                                                  \
    typedef struct type##_iterator                                                                 \
    {                                                                                              \
        type *iterator;                                                                            \
        int len;                                                                                   \
        struct type##_iterator (*map)(type(*func)(type, int), struct type##_iterator iterator);    \
        int (*find)(int (*func)(type, int), struct type##_iterator iterator);                      \
        int (*some)(type var, struct type##_iterator iterator);                                    \
        int (*every)(type var, struct type##_iterator iterator);                                   \
        int (*indexOf)(type var, struct type##_iterator iterator);                                 \
        struct type##_iterator (*sort)(struct type##_iterator iterator, int direction);            \
        struct type##_iterator (*filter)(int (*func)(type, int), struct type##_iterator iterator); \
        struct type##_iterator (*splice)(int from, int to, struct type##_iterator iterator);       \
    } type##_iterator;

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

#define iterator_find(type, func, iterator) \
    for (int i = 0; i < iterator.len; i++)  \
    {                                       \
        if (func(iterator.iterator[i], i))  \
        {                                   \
            return 1;                       \
        }                                   \
    }                                       \
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

#define iterator_filter(type, func, iterator)       \
    int len = 0;                                    \
    for (int i = 0; i < iterator.len; i++)          \
    {                                               \
        if (func(iterator.iterator[i], i))          \
        {                                           \
            len++;                                  \
        }                                           \
    }                                               \
    type *newArr = new (type, len);                 \
    int index = 0;                                  \
    for (int i = 0; i < iterator.len; i++)          \
    {                                               \
        if (func(iterator.iterator[i], i))          \
        {                                           \
            newArr[index++] = iterator.iterator[i]; \
        }                                           \
    }                                               \
    return init_iterator(type, newArr, len);

struct int_iterator f_int_init(int *arr, int len);
struct short_iterator f_short_init(short *arr, int len);
struct float_iterator f_float_init(float *arr, int len);
struct double_iterator f_double_init(double *arr, int len);
struct char_iterator f_char_init(char *arr, int len);

def_iterator_struct(int);
def_iterator_struct(short);
def_iterator_struct(float);
def_iterator_struct(double);
def_iterator_struct(char);

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct int_iterator int_map(int (*func)(int, int), struct int_iterator iterator)
{
    iterator_map(int, func, iterator);
}

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct short_iterator short_map(short (*func)(short, int), struct short_iterator iterator)
{
    iterator_map(short, func, iterator);
}

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct float_iterator float_map(float (*func)(float, int), struct float_iterator iterator)
{
    iterator_map(float, func, iterator);
}

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct double_iterator double_map(double (*func)(double, int), struct double_iterator iterator)
{
    iterator_map(double, func, iterator);
}

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct char_iterator char_map(char (*func)(char, int), struct char_iterator iterator)
{
    iterator_map(char, func, iterator);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
int int_find(int (*func)(int, int), struct int_iterator iterator)
{
    iterator_find(int, func, iterator);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
int short_find(int (*func)(short, int), struct short_iterator iterator)
{
    iterator_find(short, func, iterator);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
int float_find(int (*func)(float, int), struct float_iterator iterator)
{
    iterator_find(float, func, iterator);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
int double_find(int (*func)(double, int), struct double_iterator iterator)
{
    iterator_find(double, func, iterator);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
int char_find(int (*func)(char, int), struct char_iterator iterator)
{
    iterator_find(char, func, iterator);
}

/**
 * @brief Whether at least one element in the array has the exact value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int int_some(int var, struct int_iterator iterator)
{
    iterator_some(int, var, iterator);
}

/**
 * @brief Whether at least one element in the array has the exact value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int float_some(float var, struct float_iterator iterator)
{
    iterator_some(float, var, iterator);
}

/**
 * @brief Whether at least one element in the array has the exact value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int short_some(short var, struct short_iterator iterator)
{
    iterator_some(short, var, iterator);
}

/**
 * @brief Whether at least one element in the array has the exact value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int double_some(double var, struct double_iterator iterator)
{
    iterator_some(double, var, iterator);
}

/**
 * @brief Whether at least one element in the array has the exact value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int char_some(char var, struct char_iterator iterator)
{
    iterator_some(char, var, iterator);
}

/**
 * @brief Whether every element in the array has the same value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int int_every(int var, struct int_iterator iterator)
{
    iterator_every(int, var, iterator);
}

/**
 * @brief Whether every element in the array has the same value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int short_every(short var, struct short_iterator iterator)
{
    iterator_every(short, var, iterator);
}

/**
 * @brief Whether every element in the array has the same value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int float_every(float var, struct float_iterator iterator)
{
    iterator_every(float, var, iterator);
}

/**
 * @brief Whether every element in the array has the same value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int double_every(double var, struct double_iterator iterator)
{
    iterator_every(double, var, iterator);
}

/**
 * @brief Whether every element in the array has the same value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int char_every(char var, struct char_iterator iterator)
{
    iterator_every(char, var, iterator);
}

/**
 * @brief Gets the index of the given parameter
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return index or -1 in case of failure
 */
int int_indexOf(int var, struct int_iterator iterator)
{
    iterator_indexOf(int, var, iterator);
}

/**
 * @brief Gets the index of the given parameter
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return index or -1 in case of failure
 */
int short_indexOf(short var, struct short_iterator iterator)
{
    iterator_indexOf(short, var, iterator);
}

/**
 * @brief Gets the index of the given parameter
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return index or -1 in case of failure
 */
int float_indexOf(float var, struct float_iterator iterator)
{
    iterator_indexOf(float, var, iterator);
}

/**
 * @brief Gets the index of the given parameter
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return index or -1 in case of failure
 */
int double_indexOf(double var, struct double_iterator iterator)
{
    iterator_indexOf(double, var, iterator);
}

/**
 * @brief Gets the index of the given parameter
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return index or -1 in case of failure
 */
int char_indexOf(char var, struct char_iterator iterator)
{
    iterator_indexOf(char, var, iterator);
}

/**
 * @brief Sort the array and return the sorted value
 * @param[in] iterator struct object
 * @param[in] direction `0` or `1` for ASC and DESC
 * @return the sorted array
 */
struct int_iterator int_sort(struct int_iterator iterator, int direction)
{
    iterator_sort(int, iterator, direction);
}

/**
 * @brief Sort the array and return the sorted value
 * @param[in] iterator struct object
 * @param[in] direction `0` or `1` for ASC and DESC
 * @return the sorted array
 */
struct short_iterator short_sort(struct short_iterator iterator, int direction)
{
    iterator_sort(short, iterator, direction);
}

/**
 * @brief Sort the array and return the sorted value
 * @param[in] iterator struct object
 * @param[in] direction `0` or `1` for ASC and DESC
 * @return the sorted array
 */
struct float_iterator float_sort(struct float_iterator iterator, int direction)
{
    iterator_sort(float, iterator, direction);
}

/**
 * @brief Sort the array and return the sorted value
 * @param[in] iterator struct object
 * @param[in] direction `0` or `1` for ASC and DESC
 * @return the sorted array
 */
struct double_iterator double_sort(struct double_iterator iterator, int direction)
{
    iterator_sort(double, iterator, direction);
}

/**
 * @brief Sort the array and return the sorted value
 * @param[in] iterator struct object
 * @param[in] direction `0` or `1` for ASC and DESC
 * @return the sorted array
 */
struct char_iterator char_sort(struct char_iterator iterator, int direction)
{
    iterator_sort(char, iterator, direction);
}

/**
 * @brief Filters the array by condition
 * @param[in] condition `>` or `<` are valid
 * @param[in] var the value to be evaluated
 * @param[in] iterator struct object
 * @return the sorted array
 * @warning `(struct int_iterator).iterator` must be freed
 */
struct int_iterator int_filter(int (*func)(int, int), struct int_iterator iterator)
{
    iterator_filter(int, func, iterator);
}

/**
 * @brief Filters the array by condition
 * @param[in] condition `>` or `<` are valid
 * @param[in] var the value to be evaluated
 * @param[in] iterator struct object
 * @return the sorted array
 * @warning `(struct int_iterator).iterator` must be freed
 */
struct short_iterator short_filter(int (*func)(short, int), struct short_iterator iterator)
{
    iterator_filter(short, func, iterator);
}

/**
 * @brief Filters the array by condition
 * @param[in] condition `>` or `<` are valid
 * @param[in] var the value to be evaluated
 * @param[in] iterator struct object
 * @return the sorted array
 * @warning `(struct int_iterator).iterator` must be freed
 */
struct float_iterator float_filter(int (*func)(float, int), struct float_iterator iterator)
{
    iterator_filter(float, func, iterator);
}

/**
 * @brief Filters the array by condition
 * @param[in] condition `>` or `<` are valid
 * @param[in] var the value to be evaluated
 * @param[in] iterator struct object
 * @return the sorted array
 * @warning `(struct int_iterator).iterator` must be freed
 */
struct double_iterator double_filter(int (*func)(double, int), struct double_iterator iterator)
{
    iterator_filter(double, func, iterator);
}

/**
 * @brief Filters the array by condition
 * @param[in] condition `>` or `<` are valid
 * @param[in] var the value to be evaluated
 * @param[in] iterator struct object
 * @return the sorted array
 * @warning `(struct int_iterator).iterator` must be freed
 */
struct char_iterator char_filter(int (*func)(char, int), struct char_iterator iterator)
{
    iterator_filter(char, func, iterator);
}

struct int_iterator int_splice(int from, int to, struct int_iterator iterator)
{
    iterator_splice(int, iterator, from, to);
}

struct short_iterator short_splice(int from, int to, struct short_iterator iterator)
{
    iterator_splice(short, iterator, from, to);
}

struct float_iterator float_splice(int from, int to, struct float_iterator iterator)
{
    iterator_splice(float, iterator, from, to);
}

struct double_iterator double_splice(int from, int to, struct double_iterator iterator)
{
    iterator_splice(double, iterator, from, to);
}

struct char_iterator char_splice(int from, int to, struct char_iterator iterator)
{
    iterator_splice(char, iterator, from, to);
}

/**
 * @brief Initializes an iterator for an int
 * @param[in] arr pointer to the first element of the array
 * @param[in] len length of the array
 * @return the initialied struct object
 */
struct int_iterator f_int_init(int *arr, int len)
{
    struct int_iterator iterator = {
        iterator.iterator = arr,
        iterator.len = len,
        iterator.map = int_map,
        iterator.find = int_find,
        iterator.some = int_some,
        iterator.every = int_every,
        iterator.indexOf = int_indexOf,
        iterator.sort = int_sort,
        iterator.filter = int_filter,
        iterator.splice = int_splice};
    return iterator;
}

/**
 * @brief Initializes an iterator for an int32
 * @param[in] arr pointer to the first element of the array
 * @param[in] len length of the array
 * @return the initialied struct object
 */
struct short_iterator f_short_init(short *arr, int len)
{
    struct short_iterator iterator = {
        iterator.iterator = arr,
        iterator.len = len,
        iterator.map = short_map,
        iterator.find = short_find,
        iterator.some = short_some,
        iterator.every = short_every,
        iterator.indexOf = short_indexOf,
        iterator.sort = short_sort,
        iterator.filter = short_filter,
        iterator.splice = short_splice};
    return iterator;
}

/**
 * @brief Initializes an iterator for an int32
 * @param[in] arr pointer to the first element of the array
 * @param[in] len length of the array
 * @return the initialied struct object
 */
struct float_iterator f_float_init(float *arr, int len)
{
    struct float_iterator iterator = {
        iterator.iterator = arr,
        iterator.len = len,
        iterator.map = float_map,
        iterator.find = float_find,
        iterator.some = float_some,
        iterator.every = float_every,
        iterator.indexOf = float_indexOf,
        iterator.sort = float_sort,
        iterator.filter = float_filter,
        iterator.splice = float_splice};
    return iterator;
}

/**
 * @brief Initializes an iterator for an int32
 * @param[in] arr pointer to the first element of the array
 * @param[in] len length of the array
 * @return the initialied struct object
 */
struct double_iterator f_double_init(double *arr, int len)
{
    struct double_iterator iterator = {
        iterator.iterator = arr,
        iterator.len = len,
        iterator.map = double_map,
        iterator.find = double_find,
        iterator.some = double_some,
        iterator.every = double_every,
        iterator.indexOf = double_indexOf,
        iterator.sort = double_sort,
        iterator.filter = double_filter,
        iterator.splice = double_splice};
    return iterator;
}

/**
 * @brief Initializes an iterator for an int32
 * @param[in] arr pointer to the first element of the array
 * @param[in] len length of the array
 * @return the initialied struct object
 */
struct char_iterator f_char_init(char *arr, int len)
{
    struct char_iterator iterator = {
        iterator.iterator = arr,
        iterator.len = len,
        iterator.map = char_map,
        iterator.find = char_find,
        iterator.some = char_some,
        iterator.every = char_every,
        iterator.indexOf = char_indexOf,
        iterator.sort = char_sort,
        iterator.filter = char_filter};
    return iterator;
}

/**
 * @brief Destroys the iterator and frees memory if needed
 * @param[in] iterator struct object
 */
void f_int_destroy(struct int_iterator iterator)
{
    if (iterator.iterator != NULL)
    {
        free(iterator.iterator);
    }
}

/**
 * @brief Destroys the iterator and frees memory if needed
 * @param[in] iterator struct object
 */
void f_short_destroy(struct short_iterator iterator)
{
    if (iterator.iterator != NULL)
    {
        free(iterator.iterator);
    }
}

/**
 * @brief Destroys the iterator and frees memory if needed
 * @param[in] iterator struct object
 */
void f_float_destroy(struct float_iterator iterator)
{
    if (iterator.iterator != NULL)
    {
        free(iterator.iterator);
    }
}

/**
 * @brief Destroys the iterator and frees memory if needed
 * @param[in] iterator struct object
 */
void f_double_destroy(struct double_iterator iterator)
{
    if (iterator.iterator != NULL)
    {
        free(iterator.iterator);
    }
}

/**
 * @brief Destroys the iterator and frees memory if needed
 * @param[in] iterator struct object
 */
void f_char_destroy(struct char_iterator iterator)
{
    if (iterator.iterator != NULL)
    {
        free(iterator.iterator);
    }
}

#endif