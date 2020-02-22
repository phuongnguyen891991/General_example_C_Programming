#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isMAC(char *s) {
    int i;
    for(i = 0; i < 12; i++) {
        if(!isxdigit(s[i]))
            return false;
    }
    return true;
}

int main()
{
    char s[13] = "abcdeG012345";
    
    if (isMAC(s))
        printf("this is mac \n");
    else
        printf("this is not mac \n");
	return 0;
}
