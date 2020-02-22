#include <stdio.h>
#include <jansson.h>
#include <unistd.h>

#define RET_ERR 1
#define RET_OK  0

static inline int jsonLoadFIle(const char* fileName, json_t **retJs)
{
    json_t *f_obj;
    json_error_t error;

    f_obj = NULL;
    if (!fileName)
    {
        printf("[%s-%d] Invalid input file name \n", __func__, __LINE__);
        return RET_ERR;
    }

    if (access(fileName, F_OK) != -1)
    {
        f_obj = json_load_file(fileName, 0, &error);
        if (!f_obj)
        {
            printf("[%s-%d] Failed to load json file (file name: %s ) \n", __func__, __LINE__, fileName);
            return RET_ERR;
        }

        (*retJs) = f_obj;
    }
    return RET_OK;
}

int main()
{
    json_t *js_obj = NULL;
    int status;

    status = jsonLoadFIle("/home/phuong_nguyen/phuong.nguyen/Example/json_example/json_file.js", &js_obj);
    if (status == RET_OK)
    {
        char *buff;
        buff = json_dumps(js_obj, 0);
        printf("buff: %s \n", buff);
        free(buff);
    }
}
