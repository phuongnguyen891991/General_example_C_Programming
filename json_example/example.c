#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include <string.h>
#include <stdint.h>

static inline int json_object_integer_validate(json_t *root_object, char *key, json_t **js_output)
{
    char *buff;
    //json_t *js_output;

    if(root_object != NULL)
    {
        *js_output = json_object_get(root_object, key);
        if (!(*js_output))
        {
            printf("Could not get_object \n");
            return 1;
        }
        else
            return 0;
    }
    return 1;
}

static inline int json_object_integer_value_validate(json_t *root_object, char *key)
{
    int ret;
    json_t *js_check = NULL;

    if(!root_object)
    {
        printf("Could not get_object \n");
        return 0;
    }

    js_check = json_object_get(root_object, key);
    if(!js_check)
    {
        printf("Could not get_object, temporary assig '0' value\n");
        ret = 0;
    }
    else
        ret = json_integer_value(js_check);

    return ret;
}

#if 0
static char *jansson_get_first_value(json_t *root_js, char* key, json_t **jsRet)
{
    //json_t *root_js = NULL;
    json_error_t  err_js;
    json_t *child_js = NULL;
    const char *tmp;
    char *ret_buf = NULL;
    int size = 0;

    (*jsRet)= json_object_get(root_js, key);
    //if (!(*jsRet)) {
    //    printf( "Input string is not JSON format error: %s\n", err_js.text);
    //    goto json_fail;
    //}

    //tmp = json_string_value(child_js);
    //if ((!tmp) && (!strlen(tmp))) {
    //    printf( "Input string is not JSON format \n");
    //    goto json_fail;
    //}

    //size = strlen(tmp);
    //ret_buf = calloc(1, size + 1);
    //if (ret_buf) {
    //    strncpy(ret_buf, tmp, size);
    //    ret_buf[size] = '\0';
    //}

json_fail:
    //json_decref(root_js);
    return ret_buf;
}
#endif

static inline uint32_t jsonArrayGetMacStringArrayValue(json_t *root_arr, uint8_t index, uint8_t (*mac_string)[6])
{
    uint32_t ret;
    json_t *js_check = NULL;
    uint8_t i;
    // char mac_buff[MULTIAP_MAC_ADDRESS_STR_LEN];
    const char *mac_buff;

    if (!root_arr)
    {
        printf("[%s-%d] Invalid Input object \n", __func__, __LINE__);
        return 0;
    }

    char *buff1=NULL;
    buff1 = json_dumps(root_arr, 0);
    printf("....root_array: %s \n", buff1);
    free(buff1);

    for (i = 0; i < index; i++)
    {
        js_check = json_array_get(root_arr, i);
        if(!js_check)
        {
            printf("[%s-%d] Could not get js array \n", __func__, __LINE__);
            return 0;
        }
        else
        {
            mac_buff = json_string_value(js_check);
            // if (strlen(mac_buff) == 13)
            // {
                sscanf(mac_buff, "%02X%02X%02X%02X%02X%02X", &mac_string[i][0],
                                                             &mac_string[i][1],
                                                             &mac_string[i][2],
                                                             &mac_string[i][3],
                                                             &mac_string[i][4],
                                                             &mac_string[i][5]);
            // }
            // else
            // {
            //     printf("[%s-%d] Invalid mac string address \n", __func__, __LINE__);
            //     memset(mac_string[i], 0x0, 6);
            // }
        }
    }
    return 1;
}

static inline json_t* jsonCreateNewObject()
{
    json_t *retJson;
    
    retJson = NULL;

    retJson = json_object();
    if(NULL == retJson)
    {
        printf("[%s-%d] Failed to alloc new object \n", __func__, __LINE__);
        return NULL;
    }
    else
    {
        printf("Create new object successfully \n");
        return retJson;
    }
}

int main()
{
    //char *js_example = "{\"hello\":\"abc\"}";
    json_t *js_example = NULL;
    json_t *js_sub_example = NULL;
    json_t *getVal = NULL;
    char *buff;

    //js_example = json_object();
    js_example = jsonCreateNewObject();
    if (!js_example)
        printf("Failed to allocated mem for js_example \n");

    return;

    js_sub_example = json_array();

    if (!js_sub_example)
        printf("Failed to allocated mem for js_example \n");

    json_object_set_new(js_example, "test", NULL);
    buff = json_dumps(js_example, 0);
    printf("%s \n", buff);
    free(buff);

    return 0;

    json_object_set_new(js_example, "test", json_integer(1234));
    json_array_append_new(js_sub_example, json_string("000102030405"));
    json_array_append_new(js_sub_example, json_string("090102030405"));
    json_object_set_new(js_example, "hello", js_sub_example);

    buff = json_dumps(js_example, 0);
    printf("....buff: %s \n", buff);
    free(buff);

    // //buff = jansson_get_first_value(js_example, "hello", &getVal);
    // if(json_object_integer_validate(js_example, "hello", &getVal))
    //     goto get_failed;

    // char *buff1=NULL;
    // buff1 = json_dumps(getVal, 0);
    // printf("....buff1: %s \n", buff1);
    // free(buff1);

    // int num;
    // num = json_object_integer_value_validate(getVal, "test");
    // printf("... num: %d \n", num);

    char *input_json = "{\"hello_nr\": 1, \"hello_arr\": [\"000102030405\"]}";
    json_t *json_arr;
    uint8_t (*mac_string)[6];
    uint32_t ret;

    mac_string = (uint8_t(*)[6])malloc(sizeof(uint8_t[6])*1);
    json_arr = json_object_get(js_example, "hello");

    char *buff1=NULL;
    buff1 = json_dumps(json_arr, 0);
    printf("....buff1: %s \n", buff1);
    free(buff1);

    ret = jsonArrayGetMacStringArrayValue(json_arr, 2, mac_string);
    printf("mac string value: %02X%02X%02X%02X%02X%02X \n", mac_string[0][0],
                                                            mac_string[0][1],
                                                            mac_string[0][2],
                                                            mac_string[0][3],
                                                            mac_string[0][4],
                                                            mac_string[0][5]);

    printf("mac string value: %02X%02X%02X%02X%02X%02X \n", mac_string[1][0],
                                                            mac_string[1][1],
                                                            mac_string[1][2],
                                                            mac_string[1][3],
                                                            mac_string[1][4],
                                                            mac_string[1][5]);

    return 0;

get_failed:
    printf("go to get failed lable \n");

    return 1;
}
