#include <stdio.h>
#include "functional.h"

int square(int value, int index)
{
    return value * value;
}

int target(int value, int index)
{
    if (value > 2 && value < 4)
    {
        return 1;
    }

    return 0;
}

int main()
{
    int _numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(_numbers) / sizeof(_numbers[0]);

    iterator(int) numbers = init_iterator(int, _numbers, length);
    iterator(int) squaredNumbers = numbers.map(square, numbers);
    iterator(int) halfNumbers = numbers.splice(0, 3, numbers);
    int targetFound = numbers.find(target, numbers);

    for (int i = 0; i < squaredNumbers.len; i++)
    {
        printf("Squared Value: %d\n", squaredNumbers.iterator[i]);
    }

    for (int i = 0; i < halfNumbers.len; i++)
    {
        printf("Halved Value: %d\n", halfNumbers.iterator[i]);
    }

    printf("Target Found: %d\n", targetFound);

    destroy_iterator(int, squaredNumbers);
    destroy_iterator(int, halfNumbers);
    return 0;
}