typedef struct stack
{
    char* data;
    struct stack* head;
    struct stack* prev;
} stack;

stack* init_stack();
void push(stack *mystack, char* str);
char* pop(stack *mystack);
