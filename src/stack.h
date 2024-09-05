typedef struct stack
{
    char* data;
    struct stack* head;
    struct stack* prev;
} stack;

stack* stack_init();
void push(stack *mystack, char* str);
char* pop(stack *mystack);
int is_empty_stack(stack *mystack);
void stack_clear(stack *mystack);
