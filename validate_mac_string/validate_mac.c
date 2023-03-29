#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAC_STRING_WITH_COLON_LEN 17
#define MAC_STRING_WITHOUT_COLON_LEN 12


/* this function will validate string of MAC address in two format
   a. Format 1: 112233445566
   b. Format 2: 11:22:33:44:55:66
*/

void validateMacStringColon(const char* macAddress)
{
    int len_of_mac = 0;
    int i = 0;
    int colon_counter = 2;

    if (macAddress == NULL) {
        printf("Invalid mac string\n");
        return;
    }
    printf("Received mac: %s \n", macAddress);

    len_of_mac = strlen(macAddress);
    printf("len of mac: %d \n", len_of_mac);
    if ((len_of_mac != 17) && (len_of_mac != 12)) {
        printf("invalid mac string led \n");
        return;
    }

    for (i = 0; i < len_of_mac; i++) {
        //if (!isdigit(macAddress[i]) && (macAddress[i] < 'A' && macAddress[i] > 'F') && (macAddress[i] < 'a' && macAddress[i] > 'f')) {
        if (!isxdigit(macAddress[i]) && (macAddress[i] != ':')) {
            printf( "Invalid MAC format \n");
            return;
        }
	//To make sure ':' which is in right potition
        if (macAddress[i] == ':') {
            printf("i: %d \n", i);
            if (i != colon_counter) {
                printf("wrong colon potition %d \n", i);
                return;
            }
            colon_counter = colon_counter+3;
        }
    }
    printf("OK\n");
    return;
}

// This function just verify character in string is in type of HEX
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
    validateMacStringColon("112233445566");
    if (isMAC(s))
        printf("this is mac \n");
    else
        printf("this is not mac \n");
	
	return 0;
}
