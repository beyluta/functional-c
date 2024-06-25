#include <stdio.h>
#include "int_functional.h"

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
    int_iterator sales = f_int_init(monthlySales, size);

    // Applying a filter
    int_iterator filteredSales = sales.filter('>', 20, sales);

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
    int_iterator underperformers = sales.filter('<', 20, sales);

    // Inflating values that underperformed
    int_iterator inflatedUnderperformers = underperformers.map(inflate, underperformers);

    // Memory cleanup
    f_int_destroy(filteredSales);
    f_int_destroy(underperformers);
    f_int_destroy(inflatedUnderperformers);

    return 0;
}