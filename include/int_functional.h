#ifndef int_ITERATOR
#define int_ITERATOR

#include <stdlib.h>
#define new_int(size) (int *)malloc(size * sizeof(int))

struct int_iterator f_int_init(int *arr, int len);

/**
 * @brief `int` struct object containing properties and functions
 */
typedef struct int_iterator
{
    int *iterator;
    int len;
    struct int_iterator (*map)(int (*func)(int, int), struct int_iterator iterator);
    int (*find)(int var, struct int_iterator iterator);
    int (*some)(int var, struct int_iterator iterator);
    int (*every)(int var, struct int_iterator iterator);
    int (*indexOf)(int var, struct int_iterator iterator);
    int *(*sort)(struct int_iterator iterator, int direction);
    struct int_iterator (*filter)(char condition, int var, struct int_iterator iterator);
} int_iterator;

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct int_iterator int_map(int (*func)(int, int), struct int_iterator iterator)
{
    int *new_iterator = new_int(iterator.len);
    for (int i = 0; i < iterator.len; i++)
    {
        new_iterator[i] = func(iterator.iterator[i], i);
    }
    return f_int_init(new_iterator, iterator.len);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
int int_find(int var, struct int_iterator iterator)
{
    for (int i = 0; i < iterator.len; i++)
    {
        if (iterator.iterator[i] == var)
        {
            return var;
        }
    }
    return 0;
}

/**
 * @brief Whether at least one element in the array has the exact value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int int_some(int var, struct int_iterator iterator)
{
    int some = 0;
    for (int i = 0; i < iterator.len; i++)
    {
        if (iterator.iterator[i] == var)
        {
            return 1;
        }
    }
    return some;
}

/**
 * @brief Whether every element in the array has the same value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int int_every(int var, struct int_iterator iterator)
{
    int every = 1;
    for (int i = 0; i < iterator.len; i++)
    {
        if (iterator.iterator[i] != var)
        {
            return 0;
        }
    }
    return every;
}

/**
 * @brief Gets the index of the given parameter
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return index or -1 in case of failure
 */
int int_indexOf(int var, struct int_iterator iterator)
{
    for (int i = 0; i < iterator.len; i++)
    {
        if (iterator.iterator[i] == var)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Sort the array and return the sorted value
 * @param[in] iterator struct object
 * @param[in] direction `0` or `1` for ASC and DESC
 * @return the sorted array
 */
int *int_sort(struct int_iterator iterator, int direction)
{
    for (int i = 0; i < iterator.len; i++)
    {
        if (direction)
        {
            for (int j = 0; j < iterator.len; j++)
            {
                if (i != j && iterator.iterator[i] < iterator.iterator[j])
                {
                    int temp = iterator.iterator[i];
                    iterator.iterator[i] = iterator.iterator[j];
                    iterator.iterator[j] = temp;
                }
            }
        }
        else
        {
            for (int j = 0; j < iterator.len; j++)
            {
                if (i != j && iterator.iterator[i] > iterator.iterator[j])
                {
                    int temp = iterator.iterator[i];
                    iterator.iterator[i] = iterator.iterator[j];
                    iterator.iterator[j] = temp;
                }
            }
        }
    }
    return iterator.iterator;
}

/**
 * @brief Filters the array by condition
 * @param[in] condition `>` or `<` are valid
 * @param[in] var the value to be evaluated
 * @param[in] iterator struct object
 * @return the sorted array
 * @warning `(struct int_iterator).iterator` must be freed
 */
struct int_iterator int_filter(char condition, int var, struct int_iterator iterator)
{
    int size = 0;
    for (int i = 0; i < iterator.len; i++) {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var) {
            size++;
        }
    }
    int *pIterator = new_int(size);
    int index = 0;
    for (int i = 0; i < iterator.len; i++) {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var) {
            pIterator[index++] = iterator.iterator[i];
        }
    }
    return f_int_init(pIterator, size);
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
        iterator.filter = int_filter};
    return iterator;
}

/**
 * @brief Destroys the iterator and frees memory if needed
 * @param[in] iterator struct object
 */
void f_int_destroy(struct int_iterator iterator) 
{
    if (iterator.iterator != NULL) {
        free(iterator.iterator);
    }
}

#endif