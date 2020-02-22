#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

int main()
{
    int val;
    Queue q;

    queueInit(&q, sizeof(int));

    for(val = 0; val < 10; val++)
    {
        enqueue(&q, &val);
        printf("The value %d has been enqueued.\n", val + 1);
    }

    printf("\n");

    queuePeek(&q, &val);

    printf("The value that is at the front of the queue is %d\n\n", val + 1);

    while(getQueueSize(&q) > 0)
    {
        dequeue(&q, &val);
        printf("%d has been dequeued.\n", val + 1);
    }

    return 0;
}
