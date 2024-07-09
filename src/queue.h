typedef struct queue
{
    char* data;
    struct queue* front;
    struct queue* rear;
    struct queue* next;

}queue;

queue* queue_init();
void enqueue(queue* myqueue, char* str);
char* dequeue(queue* myqueue);
