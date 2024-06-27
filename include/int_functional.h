#ifndef int_ITERATOR
#define int_ITERATOR

#include <stdlib.h>
#include "functional_types.h"

struct int_iterator f_int_init(int *arr, int len);

/**
 * @brief `int` struct object containing properties and functions
 */
typedef struct int_iterator
{
    int *iterator;
    int len;
    struct int_iterator (*map)(int (*func)(int, int), struct int_iterator iterator);
    int (*find)(int (*func)(int, int), struct int_iterator iterator);
    int (*some)(int var, struct int_iterator iterator);
    int (*every)(int var, struct int_iterator iterator);
    int (*indexOf)(int var, struct int_iterator iterator);
    struct int_iterator (*sort)(struct int_iterator iterator, int direction);
    struct int_iterator (*filter)(int (*func)(int, int), struct int_iterator iterator);
    struct int_iterator (*splice)(int from, int to, struct int_iterator iterator);
} int_iterator;

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

struct int_iterator int_splice(int from, int to, struct int_iterator iterator)
{
    iterator_splice(int, iterator, from, to);
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

#endif