#ifndef SHORT_ITERATOR
#define SHORT_ITERATOR

#include <stdlib.h>
#define new_short(size) (short *)malloc(size * sizeof(short))

struct short_iterator f_short_init(short *arr, int len);

/**
 * @brief `short` struct object containing properties and functions
 */
typedef struct short_iterator
{
    short *iterator;
    int len;
    struct short_iterator (*map)(short (*func)(short, int), struct short_iterator iterator);
    short (*find)(short var, struct short_iterator iterator);
    int (*some)(short var, struct short_iterator iterator);
    int (*every)(short var, struct short_iterator iterator);
    int (*indexOf)(short var, struct short_iterator iterator);
    short *(*sort)(struct short_iterator iterator, int direction);
    struct short_iterator (*filter)(char condition, short var, struct short_iterator iterator);
} short_iterator;

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct short_iterator short_map(short (*func)(short, int), struct short_iterator iterator)
{
    short *new_iterator = new_short(iterator.len);
    for (int i = 0; i < iterator.len; i++)
    {
        new_iterator[i] = func(iterator.iterator[i], i);
    }
    return f_short_init(new_iterator, iterator.len);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
short short_find(short var, struct short_iterator iterator)
{
    for (int i = 0; i < iterator.len; i++)
    {
        if (iterator.iterator[i] == var)
        {
            return var;
        }
    }
    return '\n';
}

/**
 * @brief Whether at least one element in the array has the exact value
 * @param[in] var Value to be searched
 * @param[in] iterator struct object
 * @return 0 or 1
 */
int short_some(short var, struct short_iterator iterator)
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
int short_every(short var, struct short_iterator iterator)
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
int short_indexOf(short var, struct short_iterator iterator)
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
short *short_sort(struct short_iterator iterator, int direction)
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
struct short_iterator short_filter(char condition, short var, struct short_iterator iterator)
{
    int size = 0;
    for (int i = 0; i < iterator.len; i++)
    {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var)
        {
            size++;
        }
    }
    short *pIterator = new_short(size);
    int index = 0;
    for (int i = 0; i < iterator.len; i++)
    {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var)
        {
            pIterator[index++] = iterator.iterator[i];
        }
    }
    return f_short_init(pIterator, size);
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
        iterator.filter = short_filter};
    return iterator;
}

/**
 * @brief Destroys the iterator and frees memory if needed
 * @param[in] iterator struct object
 */
int f_short_destroy(struct short_iterator iterator)
{
    if (iterator.iterator != NULL)
    {
        free(iterator.iterator);
    }
}

#endif