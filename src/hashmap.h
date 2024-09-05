#define SIZE 10
#define PRIME 13

typedef struct node_of_map
{
    char* key;
    char* val;
    struct node_of_map* next;
} node_of_map;

typedef struct hashmap
{
    node_of_map* items[SIZE];
} hashmap;

hashmap* map_init();
int hhash(char* key);
void hset(hashmap* mymap, char* key, char* val);
void del(hashmap* mymap, char* key);
char* get(hashmap mymap, char* key);
int is_empty_map(hashmap *mymap);
void map_clear(hashmap *mymap);
