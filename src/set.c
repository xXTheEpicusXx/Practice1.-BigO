#include "set.h"
#include <stdlib.h>
#include <string.h>

set *set_init()
{
    set *myset = (set *)malloc(sizeof(set));
    for (int i = 0; i < SIZE; i++)
    {
        myset->items[i] = NULL;
    }
    return myset;
}

int hash(char *key)
{
    int hash = 1;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash = (hash * PRIME + (int)key[i]) % SIZE;
    }
    return hash;
}
void add(set *myset, char *key)
{
    int ind = hash(key);
    if (!is_member(*myset, key))
    {
        node_of_set *new_node = (node_of_set *)malloc(sizeof(node_of_set));
        new_node->data = strdup(key);
        new_node->next = myset->items[ind];
        myset->items[ind] = new_node;
    }
}
void rem(set *myset, char *key)
{

    int ind = hash(key);
    node_of_set *cur = myset->items[ind];
    node_of_set *prev = NULL;
    while (cur != NULL)
    {

        if (strcmp(cur->data, key) == 0)
        {
            if (prev == NULL)
            {
                myset->items[ind] = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }
            free(cur->data);
            free(cur);

            break;
        }
        prev = cur;
        cur = cur->next;
    }
}

int is_member(set myset, char *key)
{

    int is_mem = 0;
    int ind = hash(key);
    node_of_set *cur = myset.items[ind];
    while (cur != NULL)
    {
        if (strcmp(cur->data, key) == 0)
        {
            is_mem = 1;
            break;
        }
        cur = cur->next;
    }
    return is_mem;
}

int is_empty_set(set myset)
{
    int is_empty = 1;
    for (int i = 0; i < SIZE; i++)
    {
        if (myset.items[i] != NULL)
        {
            is_empty = 0;
            break;
        }
    }
    return is_empty;
}
