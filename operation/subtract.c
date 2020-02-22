#include <stdio.h>


int main()
{
    int x,y;
    x = 9;
    y = 9;
    int a;
    
    int i;
    for(i = 0; i<9; i++)
    {
        a = x--;
        printf("[i=%d] value (x--) a=%d:\n", i, a);
    }

    for(i=0; i<9; i++)
    {
        a = --y;
        printf("[i=%d] value (--y) a=%d:\n", i, a);
    }
}
