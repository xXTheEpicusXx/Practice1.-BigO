#include "database.h"
#include "getopt.h"
#include "stdio.h"
#include "string.h"

int input_parsing(int argc, char *argv[])
{
    int error = 0;
    int opt = 0;
    int long_ind = 0;
    char *short_options = "f:q:";
    char filename[MAX_LEN_STR];
    char query[MAX_LEN_STR];
    struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"query", required_argument, 0, 'q'}};
    while ((opt = getopt_long(argc, argv, short_options, long_options, &long_ind)) != -1)
    {
        switch (opt)
        {
        case 'f':
            // сохранение названия файла БД
            strcpy(filename, optarg);
            break;
        case 'q':
            // вызов функции коротая определяет порядок действий с БД
            strcpy(query, optarg);
            char *val1;
            char *val2;
            char *cont_name;
            int com_type = 0, cont_type = 0;
            query_parsing(query, &com_type, &cont_type, &cont_name, &val1, &val2);
            printf("%s %s %s\n", cont_name, val1, val2);
            printf("%d %d\n", com_type, cont_type);
            break;
        default:
            break;
        }
    }
    return error;
}

int query_parsing(char *query, int *com_type, int *cont_type, char **cont_name, char **val1, char **val2)
{
    int error = 0;
    char *command = strtok(query, " ");
    *cont_name = strtok(NULL, " ");
    *val1 = strtok(NULL, " ");
    *val2 = strtok(NULL, " ");
    printf("%s\n", command);
    // обработка команд и типов
    if (strcmp(command, "SADD") == 0)
    {
        *com_type = SADD;
    }
    else if (strcmp(command, "SREM") == 0)
    {
        *com_type = SREM;
    }
    else if (strcmp(command, "SISMEMBER") == 0)
    {
        *com_type = SISMEMBER;
    }
    else if (strcmp(command, "SPUSH") == 0)
    {
        *com_type = SPUSH;
    }
    else if (strcmp(command, "SPOP") == 0)
    {
        *com_type = SPOP;
    }
    else if (strcmp(command, "QPUSH") == 0)
    {
        *com_type = QPUSH;
    }
    else if (strcmp(command, "QPOP") == 0)
    {
        *com_type = QPOP;
    }
    else if (strcmp(command, "HSET") == 0)
    {
        *com_type = HSET;
    }
    else if (strcmp(command, "HDEL") == 0)
    {
        *com_type = HDEL;
    }
    else if (strcmp(command, "HGET") == 0)
    {
        *com_type = HGET;
    }
    else {
        error = 1;
    }
    *cont_type = *com_type/10;
    return error;
}
