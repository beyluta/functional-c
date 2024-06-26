#include <stdio.h>
#include "functional.h"

int inflate(int sale, int index)
{
    return sale + 10;
}

int main()
{
    float f[] = {1.2, 5.5};
    int len = sizeof(f) / sizeof(f[0]);

    iterator(float) i1 = init_iterator(float, f, len);
    int find = i1.find(1.3, i1);

    printf("%d\n", find);

    return 0;
}