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