#ifndef DOUBLE_ITERATOR
#define DOUBLE_ITERATOR

#include <stdlib.h>
#define new_double(size) (double *)malloc(size * sizeof(double))

struct double_iterator f_double_init(double *arr, int len);

/**
 * @brief `double` struct object containing properties and functions
 */
typedef struct double_iterator
{
    double *iterator;
    int len;
    struct double_iterator (*map)(double (*func)(double, int), struct double_iterator iterator);
    double (*find)(double var, struct double_iterator iterator);
    int (*some)(double var, struct double_iterator iterator);
    int (*every)(double var, struct double_iterator iterator);
    int (*indexOf)(double var, struct double_iterator iterator);
    struct double_iterator (*sort)(struct double_iterator iterator, int direction);
    struct double_iterator (*filter)(char condition, double var, struct double_iterator iterator);
} double_iterator;

/**
 * @brief Accepts a callback function that is called for every element
 * @param[in] func Callback
 * @param[in] iterator struct object
 * @warning return value must be freed
 */
struct double_iterator double_map(double (*func)(double, int), struct double_iterator iterator)
{
    double *new_iterator = new_double(iterator.len);
    for (int i = 0; i < iterator.len; i++)
    {
        new_iterator[i] = func(iterator.iterator[i], i);
    }
    return f_double_init(new_iterator, iterator.len);
}

/**
 * @brief Finds an element by value
 * @param[in] var Value to be found
 * @param[in] iterator struct object
 * @return element found or 0
 */
double double_find(double var, struct double_iterator iterator)
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
int double_some(double var, struct double_iterator iterator)
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
int double_every(double var, struct double_iterator iterator)
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
int double_indexOf(double var, struct double_iterator iterator)
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
struct double_iterator double_sort(struct double_iterator iterator, int direction)
{
    double *new_iterator = new_double(iterator.len);
    for (int i = 0; i < iterator.len; i++)
    {
        new_iterator[i] = iterator.iterator[i];
    }
    struct double_iterator new_struct_iterator = f_double_init(new_iterator, iterator.len);

    for (int i = 0; i < new_struct_iterator.len; i++)
    {
        if (direction)
        {
            for (int j = 0; j < new_struct_iterator.len; j++)
            {
                if (i != j && new_struct_iterator.iterator[i] < new_struct_iterator.iterator[j])
                {
                    double temp = new_struct_iterator.iterator[i];
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
                    double temp = new_struct_iterator.iterator[i];
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
struct double_iterator double_filter(char condition, double var, struct double_iterator iterator)
{
    int size = 0;
    for (int i = 0; i < iterator.len; i++)
    {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var)
        {
            size++;
        }
    }
    double *pIterator = new_double(size);
    int index = 0;
    for (int i = 0; i < iterator.len; i++)
    {
        if (condition == '>' && iterator.iterator[i] > var || condition == '<' && iterator.iterator[i] < var)
        {
            pIterator[index++] = iterator.iterator[i];
        }
    }
    return f_double_init(pIterator, size);
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
        iterator.filter = double_filter};
    return iterator;
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

#endif