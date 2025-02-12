#include <stdio.h>
#include "screen.h"

void screen_init() {}

void print(char *str)
{
    printf("%s", str);
}

void println()
{
    printf("\n");
}

void printi(int num)
{
    printf("%d", num);
}
