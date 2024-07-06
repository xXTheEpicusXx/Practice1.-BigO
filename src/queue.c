#include "queue.h"
#include <stdlib.h>
#include <string.h>

queue *init_queue()
{
    queue* myqueue = (queue*)malloc(sizeof(queue));
    myqueue->front = NULL;
    myqueue->rear = NULL;
    myqueue->next = NULL;
    return myqueue;
}
void enqueue(queue *myqueue, char *str)
{
    queue* new_item= (queue*)malloc(sizeof(queue));
    new_item->data = strdup(str);
    new_item->next = NULL;
    if(myqueue->front == NULL) {
        myqueue->front = new_item;
        myqueue->rear = new_item;
    } else {
        myqueue->rear->next = new_item;
        myqueue->rear = new_item;
    }

}
char *dequeue(queue *myqueue)
{
    char *str = NULL;
    if(myqueue->front != NULL) {
        queue* front_item = myqueue->front;
        str = strdup(front_item->data);
        myqueue->front = front_item->next;
        free(front_item);
    } else {
        myqueue->rear = NULL;
    }
    return str;
}
