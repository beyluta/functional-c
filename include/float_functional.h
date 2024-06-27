#ifndef FLOAT_ITERATOR
#define FLOAT_ITERATOR

#include <stdlib.h>
#include "functional_types.h"

struct float_iterator f_float_init(float *arr, int len);

/**
 * @brief `float` struct object containing properties and functions
 */
typedef struct float_iterator
{
    float *iterator;
    int len;
    struct float_iterator (*map)(float (*func)(float, int), struct float_iterator iterator);
    int (*find)(int (*func)(float, int), struct float_iterator iterator);
    int (*some)(float var, struct float_iterator iterator);
    int (*every)(float var, struct float_iterator iterator);
    int (*indexOf)(float var, struct float_iterator iterator);
    struct float_iterator (*sort)(struct float_iterator iterator, int direction);
    struct float_iterator (*filter)(char condition, float var, struct float_iterator iterator);
    struct float_iterator (*splice)(int from, int to, struct float_iterator iterator);
} float_iterator;

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
 * @brief Filters the array by condition
 * @param[in] condition `>` or `<` are valid
 * @param[in] var the value to be evaluated
 * @param[in] iterator struct object
 * @return the sorted array
 * @warning `(struct int_iterator).iterator` must be freed
 */
struct float_iterator float_filter(char condition, float var, struct float_iterator iterator)
{
    iterator_filter(float, condition, var, iterator);
}

struct float_iterator float_splice(int from, int to, struct float_iterator iterator)
{
    iterator_splice(float, iterator, from, to);
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

#endif