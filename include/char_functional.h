#ifndef CHAR_ITERATOR
#define CHAR_ITERATOR

#include <stdlib.h>
#include "functional_types.h"

struct char_iterator f_char_init(char *arr, int len);

/**
 * @brief `char` struct object containing properties and functions
 */
typedef struct char_iterator
{
    char *iterator;
    int len;
    struct char_iterator (*map)(char (*func)(char, int), struct char_iterator iterator);
    char (*find)(char var, struct char_iterator iterator);
    int (*some)(char var, struct char_iterator iterator);
    int (*every)(char var, struct char_iterator iterator);
    int (*indexOf)(char var, struct char_iterator iterator);
    struct char_iterator (*sort)(struct char_iterator iterator, int direction);
    struct char_iterator (*filter)(char condition, char var, struct char_iterator iterator);
    struct char_iterator (*splice)(int from, int to, struct char_iterator iterator);
} char_iterator;

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct char_iterator char_map(char (*func)(char, int), struct char_iterator iterator)
{
    char *new_iterator = new (char, iterator.len);
    for (int i = 0; i < iterator.len; i++)
    {
        new_iterator[i] = func(iterator.iterator[i], i);
    }
    return f_char_init(new_iterator, iterator.len);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
char char_find(char var, struct char_iterator iterator)
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
int char_some(char var, struct char_iterator iterator)
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
int char_every(char var, struct char_iterator iterator)
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
int char_indexOf(char var, struct char_iterator iterator)
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
struct char_iterator char_sort(struct char_iterator iterator, int direction)
{
    char *new_iterator = new (char, iterator.len);
    for (int i = 0; i < iterator.len; i++)
    {
        new_iterator[i] = iterator.iterator[i];
    }
    struct char_iterator new_struct_iterator = f_char_init(new_iterator, iterator.len);

    for (int i = 0; i < new_struct_iterator.len; i++)
    {
        if (direction)
        {
            for (int j = 0; j < new_struct_iterator.len; j++)
            {
                if (i != j && new_struct_iterator.iterator[i] < new_struct_iterator.iterator[j])
                {
                    char temp = new_struct_iterator.iterator[i];
                    new_struct_iterator.iterator[i] = new_struct_iterator.iterator[j];
                    new_struct_iterator.iterator[j] = temp;
                }
            }
        }
        else
        {
            for (int j = 0; j < new_struct_iterator.len; j++)
            {
                if (i != j && new_struct_iterator.iterator[i] > new_struct_iterator.iterator[j])
                {
                    char temp = new_struct_iterator.iterator[i];
                    new_struct_iterator.iterator[i] = new_struct_iterator.iterator[j];
                    new_struct_iterator.iterator[j] = temp;
                }
            }
        }
    }
    return new_struct_iterator;
}

/**
 * @brief Filters the array by condition
 * @param[in] condition `>` or `<` are valid
 * @param[in] var the value to be evaluated
 * @param[in] iterator struct object
 * @return the sorted array
 * @warning `(struct int_iterator).iterator` must be freed
 */
struct char_iterator char_filter(char condition, char var, struct char_iterator iterator)
{
    int size = 0;
    for (int i = 0; i < iterator.len; i++)
    {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var)
        {
            size++;
        }
    }
    char *pIterator = new (char, size);
    int index = 0;
    for (int i = 0; i < iterator.len; i++)
    {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var)
        {
            pIterator[index++] = iterator.iterator[i];
        }
    }
    return f_char_init(pIterator, size);
}

struct char_iterator char_splice(int from, int to, struct char_iterator iterator)
{
    iterator_splice(char, iterator, from, to);
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
void f_char_destroy(struct char_iterator iterator)
{
    if (iterator.iterator != NULL)
    {
        free(iterator.iterator);
    }
}

#endif