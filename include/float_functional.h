#ifndef FLOAT_ITERATOR
#define FLOAT_ITERATOR

#include <stdlib.h>
#define new_float(size) (float *)malloc(size * sizeof(float))

struct float_iterator f_float_init(float *arr, int len);

/**
 * @brief `float` struct object containing properties and functions
 */
typedef struct float_iterator
{
    float *iterator;
    int len;
    struct float_iterator (*map)(float (*func)(float, int), struct float_iterator iterator);
    float (*find)(float var, struct float_iterator iterator);
    int (*some)(float var, struct float_iterator iterator);
    int (*every)(float var, struct float_iterator iterator);
    int (*indexOf)(float var, struct float_iterator iterator);
    float *(*sort)(struct float_iterator iterator, int direction);
    struct float_iterator (*filter)(char condition, float var, struct float_iterator iterator);
} float_iterator;

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct float_iterator float_map(float (*func)(float, int), struct float_iterator iterator)
{
    float *new_iterator = new_float(iterator.len);
    for (int i = 0; i < iterator.len; i++)
    {
        new_iterator[i] = func(iterator.iterator[i], i);
    }
    return f_float_init(new_iterator, iterator.len);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
float float_find(float var, struct float_iterator iterator)
{
    for (int i = 0; i < iterator.len; i++)
    {
        if (iterator.iterator[i] == var)
        {
            return var;
        }
    }
    return 0.0;
}

/**
 * @brief Whether at least one element in the array has the exact value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int float_some(float var, struct float_iterator iterator)
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
int float_every(float var, struct float_iterator iterator)
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
int float_indexOf(float var, struct float_iterator iterator)
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
float *float_sort(struct float_iterator iterator, int direction)
{
    for (int i = 0; i < iterator.len; i++)
    {
        if (direction)
        {
            for (int j = 0; j < iterator.len; j++)
            {
                if (i != j && iterator.iterator[i] < iterator.iterator[j])
                {
                    float temp = iterator.iterator[i];
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
                    float temp = iterator.iterator[i];
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
struct float_iterator float_filter(char condition, float var, struct float_iterator iterator)
{
    int size = 0;
    for (int i = 0; i < iterator.len; i++)
    {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var)
        {
            size++;
        }
    }
    float *pIterator = new_float(size);
    int index = 0;
    for (int i = 0; i < iterator.len; i++)
    {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var)
        {
            pIterator[index++] = iterator.iterator[i];
        }
    }
    return f_float_init(pIterator, size);
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
        iterator.filter = float_filter};
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