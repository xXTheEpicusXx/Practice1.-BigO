#define MAX_LEN_STR 100

//коды команд
#define SADD 11
#define SREM 12
#define SISMEMBER 13
#define SPUSH 21
#define SPOP 22
#define QPUSH 31
#define QPOP 32
#define HSET 41
#define HDEL 42
#define HGET 43

//коды типов контейнеров
#define SET 1
#define STACK 2
#define QUEUE 3
#define HASHMAP 4

int input_parsing(int argc, char *argv[]);
int query_parsing(char *query, int *com_type, int *cont_type, char **cont_name, char **val1, char **val2);
