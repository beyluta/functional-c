#include <stdio.h>
#include "functional.h"

int inflate(int sale, int index)
{
    printf("%d and index %d\n", sale, index);
    return 666;
}

int main()
{
    // Array (can also be heap allocated)
    int monthlySales[] = {15, 40, 30, 34, 34, 23, 33, 8, 3, 4, 18, 5};
    int size = sizeof(monthlySales) / sizeof(monthlySales[0]);

    // Initializing the struct
    iterator(int) sales = init_iterator(int, monthlySales, size);
    iterator(int) updated = sales.map(inflate, sales);

    printf("%d\n", updated.iterator[0]);

    return 0;
}