#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() function
#include <jansson.h>

#define IPv4_LEN    32
#define MAC_LEN    18
#define HOSTNAME_LEN    128
#define CLIENT_ID_LEN   22

#define EXPIRATION  "expiration"
#define RAW_IP  "ip"
#define CLIENT_ID   "clientID"

#define INDENT_NO   1

struct dev_raw_info {
    char expiration[128];
    char mac[MAC_LEN];
    char ip[IPv4_LEN];
    char hostname[HOSTNAME_LEN];
    char clientID[CLIENT_ID_LEN];
};

int write_json_to_file(const char *array, const char *path_file)
{
    int ret;
    json_t *json;

    json_t* js_array = NULL;
    js_array = json_loadb(array, strlen(array), 0, NULL);
    if(!js_array)
        printf("error \n");

    ret = json_dump_file(js_array, path_file, JSON_INDENT(INDENT_NO));
    if (ret == -1 )
    {
        printf("failt to write json file\n");
        return -1;
    }
    return 0;
}

int write_to_json_format(struct dev_raw_info dev_online, json_t* root_jobj)
{
    char *result;

    //root_jobj = json_object();

    json_t *jobj = json_object();
    json_object_set_new(jobj, EXPIRATION, json_string(dev_online.expiration));
    json_object_set_new(jobj, RAW_IP, json_string(dev_online.ip));
    json_object_set_new(jobj, CLIENT_ID, json_string(dev_online.clientID));

    json_object_set_new(root_jobj, "raw_data", jobj);

    json_t *jobj1 = json_object();
    json_object_set_new(jobj1, EXPIRATION, json_string(dev_online.expiration));
    json_object_set_new(jobj1, RAW_IP, json_string(dev_online.ip));
    json_object_set_new(jobj1, CLIENT_ID, json_string(dev_online.clientID));

    
    json_object_set_new(root_jobj, "cif_data", jobj);
    //result = json_dumps(root_jobj, 0);
    //if (result)
    //{
    //    printf("%s\n", result);
    //    sprintf(msg, "%s", result);
    //    free(result);
    //}

    //json_decref(jobj);
}

int agent_parse_raw_data(char *str, struct dev_raw_info *raw_data) {
    const char s[2] = " ";
    int cnt = 0;
    char *token;
    char *strtoint;
    
    /* get the first token */
    token = strtok(str, s);
    
    /* walk through other tokens */
    while(token != NULL)
    {
        switch(cnt)
        {
           case 0:
                /*expiration time*/
                snprintf(raw_data->expiration, strlen(token), "%s", token);
                break;
           case 1:
                /*mac address*/
                snprintf(raw_data->mac, MAC_LEN, "%s", token);
                break;
           case 2:
                /*Ip address*/                 
                snprintf(raw_data->ip, IPv4_LEN -1, "%s", token);       
                break;
           case 3:
                /*hostname*/
                snprintf(raw_data->hostname, HOSTNAME_LEN -1, "%s", token);
                break;
           case 4:
               /*client-ID*/
               snprintf(raw_data->clientID, CLIENT_ID_LEN -1, "%s", token);
               break;
           default:
               break;
        }
     
        token = strtok(NULL, s);
        cnt++;
    }
    
    return(0);
}

int process_raw_data_from_file(const char *ip, const char *mac, struct dev_raw_info *raw_data)
{
    FILE *file;
    //struct dev_raw_info raw_data;
    char *msg;
    int device_detected = 0;
    json_t *jobj;
    jobj = json_object();
    if (NULL == jobj)
    {
        printf("Error! created jboj \n");
        return -1;
    }

    if ((file = fopen("dnsmasq.leases", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        return -1;      
    }

    if ((NULL == ip) && (NULL == mac))
        return -1;

    char line[128]; /* or other suitable maximum line size */

    while (fgets(line, sizeof line, file) != NULL) /* read a line */
    {
         //puts(line); /* write the line */
         agent_parse_raw_data(line, raw_data);
         printf("%s\n", raw_data->mac);
         printf("%s\n", raw_data->ip);             

         if ((!strncmp(raw_data->ip, ip, 32)) && (!strncmp(raw_data->mac, mac, 32)))
         {
            write_to_json_format(*raw_data, jobj);
            msg = json_dumps(jobj, 0);
            printf("------%s \n", msg);
            device_detected = 1;
            break;
         }
         //continue;
    }
    
    if (!device_detected)
    {
        printf("can not find device \n");
        json_decref(jobj);
        return -1;
    }

    fclose(file);
    
    return 0;
}

int main()
{
    int ret;
    char ip[] = "10.253.1.559";
    char mac[] = "b8:27:eb:8c:2a:8c";
    struct dev_raw_info raw_data;

    ret = process_raw_data_from_file(ip, mac, &raw_data);
    if (ret != 0)
        printf("Error to get data \n");

}
