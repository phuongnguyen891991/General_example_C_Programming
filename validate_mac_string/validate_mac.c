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

// validate mac 2
int ValidateMACAddress(unsigned char *mac)
{
	int i, j;
	unsigned char str[12], value[15];
	unsigned int mac_val = 0;

	memset(str, 0x00, sizeof(str));
	memset(value, 0x00, sizeof(value));

	if (mac == NULL) {
		printf("Null MAC Address\n");
		mac_usage();
		return -1;
	}
	/* Total MAC Address Len should be <=17 */
	else if (strlen((const char *)mac) > 17) {
		printf("Invalid MAC Address length\n");
		mac_usage();
		return -1;
	} else {
		/* Tokenize each field in MAC Address seperator 
		 * Seperator ':' is only handled */
		for (i = 2, j = 0; i <= 17; i += 3) {
			str[j] = mac[i - 2];
			j++;
			str[j] = mac[i - 1];
			j++;
			if (mac[i] != ':' && i < 17) {
				printf("Wrong MAC Address Format\n");
				mac_usage();
				return -1;
			}
		}
	}

	/* Validate each filed in MAC Address 
	 * The fileds should be in the range [0-9][A-F] */
	for (i = 0; i < 12; i++) {
		if (isalpha(str[i]))
			str[i] = toupper(str[i]);
		if ((str[i] < '0') || (str[i] > '9')) {
			if ((str[i] < 'A') || (str[i] > 'F')) {
				printf("Wrong MAC Address Fields\n");
				mac_usage();
				return -1;
			} else {
				if ((str[i] >= 'A') && (str[i] <= 'F'))
					str[i] -= ('A' - 10);
			}
		} else {
			if ((str[i] >= '0') && (str[i] <= '9'))
				str[i] -= '0';
		}
	}

	/* Sum up each Byte in MAC Address */
	for (i = 0; i < 12 / 2; i++) {
		value[i] = (str[i << 1] << 4) + str[(i << 1) + 1];
		mac_val += value[i];
	}

	if (mac_val) {
		/* Check if any address is a MAC broadcast address FF:FF:FF:FF:FF:FF 
		 * mac_val + MAX_LAN_MAC_ADDR + MAX_WAN_MAC_ADDR >= FF:FF:FF:FF:FF:FF
		 * MAC Address is a broadcast */
		if ((mac_val + MAX_LAN_MAC_ADDR + MAX_WAN_MAC_ADDR) >=
		    1530) {
			printf("MAC Address results in Broadcast Address!\n");
			mac_usage();
			return -1;
		} else
			return 0;
	} else {
		printf("ZERO - MAC Address Invalid!");
		mac_usage();
		return -1;
	}
}

int wlan_is_valid_mac(const char* mac)
{
    int i = 0;
    int s = 0;

    while (*mac) {
        if (isxdigit(*mac)) {
            i++;
        } else if (*mac == ':' || *mac == '-') {
            if (i == 0 || i / 2 - 1 != s)
                break;
            ++s;
        } else {
            s = -1;
        }
        ++mac;
    }
    return (i == 12 && (s == 5 || s == 0));
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
