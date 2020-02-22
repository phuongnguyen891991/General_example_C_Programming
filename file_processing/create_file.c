#include <stdio.h>
#include <fcntl.h>

int create_file(const char *str, const char* filename)
{
    FILE *fp;
    mode_t mode;
    int check;

    fp = fopen(filename, "r");
    if (NULL == fp)
    {
        check = creat(filename, S_IRWXU);
        if (check < 0)
        {
            printf("Create file error \n");
        }
        return 0;
    }
    printf("File is not existed\n");
    return 1;
}

int main()
{
    char filename[256] = "create_test.txt";
    char str[256] = "this is string";
    create_file(str, filename);

    return 0;
}

