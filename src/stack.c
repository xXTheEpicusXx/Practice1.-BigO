#include "stack.h"
#include <stdlib.h>
#include <string.h>

stack *stack_init()
{
    stack *mystack = (stack *)malloc(sizeof(stack));
    mystack->head = NULL;
    mystack->prev = NULL;
    return mystack;
}
void push(stack *mystack, char *str)
{
    stack *new_item = (stack *)malloc(sizeof(stack));
    new_item->data = strdup(str);
    new_item->prev = mystack->head;
    mystack->head = new_item;
}
char *pop(stack *mystack)
{
    if (!is_empty_stack(mystack))
    {
        char *str = NULL;
        if (mystack->head != NULL)
        {

            stack *head_item = mystack->head;
            str = strdup(head_item->data);
            mystack->head = head_item->prev;
            free(head_item);
        }
        return str;
    }
    else
        return "NULL";
}

int is_empty_stack(stack *mystack)
{
    return mystack->head == NULL;
}

void stack_clear(stack *mystack)
{
    while (mystack->head != NULL)
    {
        pop(mystack);
    }
    free(mystack);
}
