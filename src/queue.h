typedef struct queue
{
    char* data;
    struct queue* front;
    struct queue* rear;
    struct queue* next;

}queue;

queue* init_queue();
void enqueue(queue* myqueue, char* str);
char* dequeue(queue* myqueue);
