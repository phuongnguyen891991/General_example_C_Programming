#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>


void convertStringToMacFromFormat(const char *input_str, uint8_t *out_mac)
{
    if((!input_str) || (strlen(input_str) != 12))
    {
        printf("[%s-%d] Input string should not null \n", __func__, __LINE__);
    }
    else
    {
        sscanf(input_str, "%02X%02X%02X%02X%02X%02X", &out_mac[0], &out_mac[1],
                                                      &out_mac[2], &out_mac[3],
                                                      &out_mac[4], &out_mac[5]);

        printf("[%s-%d] The entry MAC:  %02X%02X%02X%02X%02X%02X \n", __func__, __LINE__,
                                                                   out_mac[0], out_mac[1],
                                                                   out_mac[2], out_mac[3],
                                                                   out_mac[4], out_mac[5]);
    }
}

void main()
{
    char mac_str[]= "000102030405";
    uint8_t *mac;

    printf("len of string : %d \n", strlen(mac_str));
    mac = (uint8_t*)malloc(sizeof(uint8_t)*6);
    convertStringToMacFromFormat(mac_str, mac);
    return;
}
