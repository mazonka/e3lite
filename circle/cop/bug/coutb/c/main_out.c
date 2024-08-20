
#include "cir.out.c"

#include <stdio.h>

#include "main.h"

int main()
{
    int i, j;
    char x[X];
    char y[Y];

    for (i = 0; i < X; i++) x[i] = (char)0;

    FUNNout(x, y);

    for (i = 0; i < X; i++) printf("%d", (int)x[i]);
    printf(" ");
    for (i = 0; i < Y; i++) printf("%d", (int)y[i]);
}
