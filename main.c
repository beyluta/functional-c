#include <stdio.h>
#include "functional.h"

int square(int value, int index)
{
    return value * value;
}

int filter(int value, int index)
{
    return value > 50;
}

int hundreds(int value, int index)
{
    return value >= 100;
}

int lower(int value, int index)
{
    return value <= 50;
}

int find(int value, int index)
{
    return value == 81;
}

int main()
{
    int arrPtr[] = {3, 9, 12};
    array(int) arr = to_array(int, arrPtr, sizeof(arrPtr) / sizeof(arrPtr[0]));

    array(int) squared = arr.map(square, arr);
    for (int i = 0; i < squared.len; i++)
    {
        printf("Squared: %d\n", squared.array[i]);
    }

    array(int) filtered = squared.filter(filter, squared);
    for (int i = 0; i < filtered.len; i++)
    {
        printf("Filtered: %d\n", filtered.array[i]);
    }

    int isHundreds = filtered.some(hundreds, filtered);
    printf("Is there any value in the hundreds? %d\n", isHundreds);

    int isLower = filtered.every(lower, filtered);
    printf("Are all values lower than 50? %d\n", isLower);

    int found = filtered.find(find, filtered);
    printf("Target has been found: %s\n", found ? "Yes" : "No");

    int index = filtered.indexOf(144, filtered);
    printf("Index of 144 is: %d\n", index);

    array(int) sliced = squared.slice(0, 2, squared);
    for (int i = 0; i < sliced.len; i++)
    {
        printf("Sliced: %d\n", sliced.array[i]);
    }

    array(int) sorted = sliced.sort(sliced, 0);
    for (int i = 0; i < sorted.len; i++)
    {
        printf("Sorted: %d\n", sorted.array[i]);
    }

    destroy_array(int, squared);
    destroy_array(int, filtered);
    destroy_array(int, sliced);
    destroy_array(int, sorted);

    return 0;
}