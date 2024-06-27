# Functional C Library

A collection of functions to manipulate primitive type arrays like you would in a modern functional language.

```c
#include "functional.h"
```

## Usage

1- Create or have an array of the following primitive types: `int`, `short`, `double`, `float`, `char`.

2- Then you may call the function `init_iterator(type, arrPtr, size)` to get a struct representing your array.

```c
#include <stdio.h>
#include "functional.h"

float square(float value, int index)
{
    return value * value;
}

int target(float value, int index)
{
    if (value > 2 && value < 4)
    {
        return 1;
    }

    return 0;
}

int higher(float value, int index)
{
    if (value >= 4)
    {
        return 1;
    }

    return 0;
}

int main()
{
    float _numbers[] = {1.5, 2, 3, 4, 5};
    int length = sizeof(_numbers) / sizeof(_numbers[0]);

    iterator(float) numbers = init_iterator(float, _numbers, length);
    iterator(float) squaredNumbers = numbers.map(square, numbers);
    iterator(float) halfNumbers = numbers.splice(0, 3, numbers);
    iterator(float) filtered = numbers.filter(higher, numbers);
    int targetFound = numbers.find(target, numbers);

    destroy_iterator(float, squaredNumbers);
    destroy_iterator(float, halfNumbers);
    destroy_iterator(float, filtered);
    return 0;
}
```
