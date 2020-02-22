#include <stdio.h>
#include <jansson.h>
#include <string.h>

#define INDENT_NO   1
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

int main()
{
    int ret;
    const char* path_file = "example.json";
    const char* array = "{\"raw_data\": {\"expiration\": \"1525923959\", \"ip\": \"10.231.1.224\", \"clientID\": \"01:b8:27:eb:8c:2a:8c\"}}";

    ret = write_json_to_file(array, path_file);
}
