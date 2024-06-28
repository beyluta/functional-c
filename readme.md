# Functional C Library

A collection of functions to manipulate primitive type arrays like you would in a modern functional language.

```c
#include "functional.h"
```

## Usage

Create or have an array of the following primitive types: `int`, `short`, `double`, `long`, `float`, `char`.<br>Then you may call the function `to_array(type, arrPtr, size)` to get a struct representing your array.

```c
int arrPtr[] = {3, 9, 12}; // May also be heap allocated
array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
```

## Memory Management

If your array is allocated in the heap, you must call `destroy_array(int, arr)`

```c
int main()
{
    int *pArr = (int*)malloc(sizeof(int) * 4);
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    destroy_array(int, arr);
}
```

Likewise, if any function other than a stack-allocated `to_array(type, arrPtr, size)` returns an array, then you must call `destroy_array(int, arr)`

```c
int main()
{
    int arrPtr[] = {3, 9, 12}; // <- Stack allocated

    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    array(int) sorted = arr.sort(arr, 0);

    // destroy_array(int, arr); // Not needed because `arr` is stack allocated
    destroy_array(int, sorted); // Needed because sorted is heap-allocated
}
```

## Functions

Every instance of an array struct contains pointers to functions that can be accessed from the object itself.

### Map

.map() creates a new array by calling a function on every element of the original array and stores the new values as a new array.

```c
int arrPtr[] = {3, 9, 12};

int square(int value, int index)
{
    return value * value;
}

int main()
{
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    array(int) squared = arr.filter(square, arr);
    for (int i = 0; i < arr.len; i++)
    {
        printf("Squared: %d\n", squared.array[i]);
    }
}
```

### Filter

.filter() method creates a new array with elements that pass the conditions provided by a function.

```c
int arrPtr[] = {3, 9, 12};

int filter(int value, int index)
{
    return value > 50;
}

int main()
{
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    array(int) filtered = arr.filter(filter, arr);
    for (int i = 0; i < arr.len; i++)
    {
        printf("Filtered: %d\n", arr.array[i]);
    }
}
```

### Find

.find() returns a truthy value if the conditions of the given function are met by any of the elements in the array.

```c
int arrPtr[] = {3, 9, 12};

int find(int value, int index)
{
    return value == 9;
}

int main()
{
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    int found = arr.find(find, arr);
    printf("Target has been found: %s\n", found ? "Yes" : "No");
}
```

### Some

.some() calls a provided function for each element in an array, until the it returns a truthy value.

```c
int arrPtr[] = {3, 9, 12};

int hundreds(int value, int index)
{
    return value >= 100;
}

int main()
{
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    int isHundreds = arr.some(hundreds, arr);
    printf("Is there any value in the hundreds? %d\n", isHundreds);
}
```

### Every

.every() calls a provided function once for each element in an array, until it returns a falsy value.

```c
int arrPtr[] = {3, 9, 12};

int lower(int value, int index)
{
    return value <= 50;
}

int main()
{
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    int isLower = arr.every(lower, arr);
    printf("Are all values lower than 50? %d\n", isLower);
    return 0;
}
```

### Index Of

.indexOf() returns the index of the first occurence of a given element in the array. If nothing is found -1 is returned.

```c
int arrPtr[] = {3, 9, 12};

int main()
{
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    int index = arr.indexOf(12, filtered);
    printf("Index of 12 is: %d\n", index);
}
```

### Slice

.slice() removes a section of the array and returns the elements as a new array

```c
int arrPtr[] = {3, 9, 12};

int main()
{
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    array(int) sliced = arr.slice(0, 1, arr);
    for (int i = 0; i < sliced.len; i++)
    {
        printf("Sliced: %d\n", sliced.array[i]);
    }
}
```

### Sort

.sort() sorts the array in either direction `ascending` or `descending` by the given `direction` parameter.

```c
int arrPtr[] = {3, 9, 12};

int main()
{
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));
    array(int) sorted = arr.sort(arr, 0);
    for (int i = 0; i < sorted.len; i++)
    {
        printf("Sorted: %d\n", sorted.array[i]);
    }
}
```
