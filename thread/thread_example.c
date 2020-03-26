// gcc -o thread_example thread_example.c -lpthread

#include<stdio.h>
#include<pthread.h>
#include<stdint.h>

uint8_t flags;


void *function()
{
    flags = 1;
    printf("Hello world \n");
    return NULL;
}

void main()
{
    pthread_t thread_id;
    uint8_t ret;

    flags = 0x0;
    for(int i = 0; i < 3; i++)
    {
        if(flags)
        {
            printf("already have threads \n");
            return;
        }
        else
        {
            ret = pthread_create(&thread_id, NULL, function, NULL);
            if(ret)
            {
                printf("Failed to create thread \n");
                return;
            }

            pthread_detach(thread_id);
            sleep(1);
        }
    }
}
