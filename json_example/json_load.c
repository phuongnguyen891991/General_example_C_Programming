// This is an example to use json lib to parser json and verify json value
// The json data need to validate are:
// {"id":"332850df-8429-407d-89b1-2938d37fe179","macAddress":"94:10:3E:E9:93:3C","serialId":"ftcspdav"}

#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


#define DEVICE_ID_KEY   "id"
#define SERIAL_ID_KEY   "serialId"
#define MAC_ADDR_KEY    "macAddress"

#define STRING_MAC_SIZE 18
#define PRINT_D(x, ...) fprintf( stdout, "%s:%s:%d: " x "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)


//remove any characteristic in string
void removeChar(char *intput_str, char c)
{
    int i, j;
    i = j = 0;

    while (intput_str[j])
    {
        if (intput_str[j] != c)
        {
            intput_str[i++] = intput_str[j];
        }
        j++;
    }

    intput_str[i] = 0;
}

//Verify mac address
bool isMAC(char *s)
{
    int i, colon;
    i = colon = 0;

    if (NULL == s)
        return false;

    // removeChar(s, ':');

    for (i = 0; i < STRING_MAC_SIZE-1; i++)
    {
        if (s[i] == ':')
        {
            if(colon >= 5)
            {
                PRINT_D("wrong mac %d \n", colon);
                return false;
            }
            colon++;
            continue;
        }

        if(!isxdigit(s[i]))
        {
            printf("%c at %d \n", s[i], i);
            return false;
        }
        printf("%c at %d \n", s[i], i);
    }
    return true;
}

bool jsonGetObjVal(char *json_string, char *key, char *out)
{
    json_t *js_obj, *js_output;
    json_error_t json_err;
    const char *buff;

    js_obj = NULL;
    js_output = NULL;

    if(json_string != NULL)
    {
        js_obj = json_loads((const char*)json_string, 0, &json_err);
        if (js_obj == NULL)
        {
            PRINT_D("msg decode error %s \"%s\"\n", json_err.text, json_err.source);
            return false;
        }

        js_output = json_object_get(js_obj, key);
        if (!js_output)
        {
            PRINT_D("Could not get_object \n");
            json_decref(js_obj);
            return false;
        }
        else
        {
            buff = json_string_value(js_output);
            strcpy(out, buff);
            PRINT_D("out string: %s \n", out);
            json_decref(js_obj);
            return true;
        }
    }
    return false;
}

bool jsonValidate(const char *input_str)
{
    json_t *post_obj;
    json_error_t json_err;

    post_obj = NULL;
    post_obj = json_loads(input_str, 0, &json_err);
    if (post_obj == NULL) {
        PRINT_D("msg decode error %s \"%s\"\n", json_err.text, json_err.source);
        return false;
    }
    json_decref(post_obj);
    return true;
}

bool jsonGetString(char *input, char *option)
{
    char str_out[64] = {0};
    bool ret;
    const char *buff;

    if (jsonValidate((const char*)input))
    {
        PRINT_D("Check and validate json \n");
        switch(*option)
        {
            case 'd':
                ret = jsonGetObjVal(input, DEVICE_ID_KEY, str_out);
                if(ret)
                {
                    PRINT_D("print out data : %s \n", str_out);
                    fprintf(stdout, "%s", str_out);
                    return true;
                }
            break;
            case 'm':
                ret = jsonGetObjVal(input, MAC_ADDR_KEY, str_out);
                if(ret)
                {
                    if(strlen(str_out) >= STRING_MAC_SIZE)
                    {
                        PRINT_D("Invalid MAC \n");
                        return false;
                    }

                    ret = isMAC(str_out);
                    if (ret)
                    {
                        PRINT_D("Is mac address \n");
                        fprintf(stdout, "%s", str_out);
                        return true;
                    }
                }
            break;
            case 's':
                ret = jsonGetObjVal(input, SERIAL_ID_KEY, str_out);
                if(ret)
                {
                    fprintf(stdout, "%s", str_out);
                    return true;
                }
            break;
            default:
            {
                return false;
            }
        }
    }
    return false;
}

bool postMessageHandler(char *post_msg)
{
    return false;
}

int main (int argc, char *argv[])
{
    char *input_str = argv[1];
    json_t *post_obj, *js_id, *js_mac, *js_ser;
    json_error_t json_err;
    int ret = 0;

    post_obj = NULL;
    js_id = NULL;
    js_mac = NULL;
    js_ser = NULL;

    if ((argc == 0) && (NULL == input_str))
    {
        PRINT_D("Have no input string \n");
        return -1;
    }
    int opt;

    // put ':' in the starting of the
    // string so that program can
    //distinguish between '?' and ':'
    while((opt = getopt(argc, argv, "v:m:d:s:")) != -1)
    {
        switch(opt)
        {
            case 'v':
                printf("option: %c\n", opt);
                ret = jsonValidate((const char*)optarg);
                if (ret)
                {
                    printf("is json \n");
                    return 0;
                }
                break;
            case 'm':
                ret = jsonGetString(optarg, "m");
                if (ret)
                    return 0;
                break;
            case 'd':
                PRINT_D("optarg: %s \n", optarg);
                ret = jsonGetString(optarg, "d");
                if (ret)
                    return 0;
                break;
            case 's':
                ret = jsonGetString(optarg, "s");
                if (ret)
                    return 0;
                break;
        }
    }

    return ret;
}