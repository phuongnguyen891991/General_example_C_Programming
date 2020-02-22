#include <stdio.h>

int main()
{
    int x = 1;
    int *p;

    p = &x;
    p = 500;
    p = p + 2;

    printf("p: %x \n",p);
    printf("*p: %d \n",*p);
    printf("&p: %d \n",&p);

    return 0;
}
