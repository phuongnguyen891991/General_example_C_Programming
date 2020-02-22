#include <string.h>
#include <stdio.h>
#define MAC_STR_LEN 18
#define IP_STR_LEN 18
#define IF_STR_LEN 8
#define DEVICEID_STR_LEN 37



struct device_online_info
{
    char deviceID[DEVICEID_STR_LEN];
    char intf[IF_STR_LEN];
    char mac[MAC_STR_LEN];
    char ipv4[MAC_STR_LEN];
};

int parse_token(char *str, char *output) {
//   char *str = "C390FD7B-8EAA-447B-BC01-856DB44FCB20,br0,b8:27:eb:8c:2a:8c,10.253.1.224,(null)";
   const char s[2] = "=";
   int cnt = 1;
   char *token;
   
   /* get the first token */
   token = strtok(str, s);
   
   /* walk through other tokens */
   while( token != NULL ) {
    if(1 == cnt)
    {
      printf( " %s\n", token );
      sscanf((const char*)token, "%s", output);
      break;
    }
    
      token = strtok(NULL, s);
      cnt++;
   }
   
   return(0);
}

int main()
{
    int ret;
    char output[40];
    struct device_online_info dev_info;
    //char str[80] = "C390FD7B-8EAA-447B-BC01-856DB44FCB20,br0,b8:27:eb:8c:2a:8c,10.253.1.224,(null)";
    char str[80] = "power_state                                   = INTERFACE_POWER_STATE_ON";
    ret = parse_token(str, dev_info.deviceID);
    if (ret != 0)
        printf("Error \n");
    printf("%s \n", dev_info.deviceID);

    return 0;
}
