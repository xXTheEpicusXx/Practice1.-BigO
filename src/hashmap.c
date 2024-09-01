#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

hashmap *map_init()
{
    hashmap *mymap = (hashmap *)malloc(sizeof(hashmap));
    for (int i = 0; i < SIZE; i++)
    {
        mymap->items[i] = NULL;
    }
    return mymap;
}

int hhash(char *key)
{
    int hash = 1;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash = (hash * PRIME + (int)key[i]) % SIZE;
    }
    return hash;
}
void hset(hashmap *mymap, char *key, char *val)
{
    int ind = hhash(key);
    node_of_map *new_node = (node_of_map *)malloc(sizeof(node_of_map));
    new_node->key = strdup(key);
    new_node->val = strdup(val);
    node_of_map *cur = mymap->items[ind];
    int may_set = 1;
    while (cur != NULL)
    {
        if (strcmp(cur->key, new_node->key) == 0)
        {
            may_set = 0;
            break;
        }
    }
    if (may_set)
    {
        new_node->next = mymap->items[ind];
        mymap->items[ind] = new_node;
    }
}
void del(hashmap *mymap, char *key)
{
    int ind = hhash(key);
    node_of_map *cur = mymap->items[ind];
    node_of_map *prev = NULL;
    while (cur != NULL)
    {

        if (strcmp(cur->key, key) == 0)
        {
            if (prev == NULL)
            {
                mymap->items[ind] = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }
            free(cur->val);
            free(cur->key);
            free(cur);

            break;
        }
        prev = cur;
        cur = cur->next;
    }
}
char *get(hashmap mymap, char *key)
{
    if (!is_empty_map(&mymap))
    {
        int ind = hhash(key);
        char *str = NULL;
        node_of_map *cur = mymap.items[ind];
        while (cur != NULL)
        {
            if (strcmp(cur->key, key) == 0)
            {
                str = strdup(cur->val);
                break;
            }
            cur = cur->next;
        }
        return str;
    }
    else
        return "NULL";
}

int is_empty_map(hashmap *mymap)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (mymap->items[i] != NULL)
        {
            return 0;
        }
    }
    return 1;
}
