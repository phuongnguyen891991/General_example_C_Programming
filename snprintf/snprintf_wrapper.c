#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

void convertToStringFromFormat(char* output, uint8_t *mac)
{
    if(!output || !mac)
    {
        printf("Invalid input variable \n");
    }

    sprintf(output, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2],
                                                mac[3], mac[4], mac[5]);
    return;
}

int main()
{
    uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    char str_mac[13] = "\0";

    convertToStringFromFormat(str_mac, mac);

    printf("string of mac are: %s \n", str_mac);
}
