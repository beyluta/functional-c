# Functional C Library

A collection of functions to manipulate primitive type arrays like you would in a modern functional language.

Include the headers for the primitive data types that you require or include all of them at once by including the `functional.h` header instead.

```c
#include "int32_functional.h"
#include "short_functional.h"
#include "double_functional.h"
#include "float_functional.h"
#include "char_functional.h"

// Or only the following to include all
#include "functional.h"
```

## Usage

Create or have an array of the following primitive types: `int`, `short`, `double`, `float`, `char`. Then you may call the function `f_int_init(ARRAY, SIZE)` to get a struct representing your array.

```c
int arr[] = { 1, 5, 10 };
int_iterator iterator = f_int_init(arr, 3);
```

The iterator has many functions to manipulate the array: `map`, `find`, `filter`, `some`, `every`, `indexOf`, `sort`. You may call the functions from the iterator itself by accessing its properties or by referencing the functions themselves.

```c
int_iterator sorted = iterator.sort(iterator, 0);
// Or by calling the function directly
int_iterator pSorted2 = int_sort(iterator, 0);
```

## Sample Application

```c
#include <stdio.h>
#include "functional.h"

int inflate(int sale, int index)
{
    return sale + 10;
}

int main()
{
    // Array (can also be heap allocated)
    int monthlySales[] = {15, 40, 30, 34, 34, 23, 33, 8, 3, 4, 18, 5};
    int size = sizeof(monthlySales) / sizeof(monthlySales[0]);

    // Initializing the struct
    iterator(int) sales = init_iterator(int, monthlySales, size);

    // Applying a filter
    iterator(int) filteredSales = sales.filter('>', 20, sales);

    // Checking whether all values are 0
    int noSales = sales.every(0, sales);

    // Checking whether the targer value 33 is found
    int targetFound = filteredSales.find(33, sales);

    if (noSales)
    {
        printf("Work Harder!");
    }

    if (targetFound)
    {
        int index = sales.indexOf(33, sales);
        printf("Target is at index %d\n", index);
    }

    // Applying a filter
    iterator(int) underperformers = sales.filter('<', 20, sales);

    // Inflating values that underperformed
    iterator(int) inflatedUnderperformers = underperformers.map(inflate, underperformers);

    // Memory cleanup
    destroy_iterator(int, filteredSales);
    destroy_iterator(int, underperformers);
    destroy_iterator(int, inflatedUnderperformers);

    return 0;
}
```
