#include <stdio.h>

int write_file(const char *str, const char* filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (NULL != fp)
    {
        fprintf(fp, "%s\n", str);
        fclose(fp);
        return 0;
    }
    printf("File is not existed\n");
    return 1;
}

int main()
{
    char filename[256] = "test.txt";
    char str[256] = "this is string";
    write_file(str, filename);

    return 0;
}

