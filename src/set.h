#define SIZE 10
#define PRIME 13

typedef struct node_of_set
{
    char *data;
    struct node_of_set *next;
} node_of_set;

typedef struct set
{
    node_of_set *items[SIZE];
} set;

set *set_init();
int hash(char *key);
void add(set *myset, char *key);
void rem(set *myset, char *key);
int is_member(set myset, char *key);
int is_empty_set(set myset);
void set_clear(set *myset);
