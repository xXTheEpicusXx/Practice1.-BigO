#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include "database.h"
#include "set.h"
#include "stack.h"
#include "queue.h"
#include "hashmap.h"

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
            // printf("%s %s %s\n", cont_name, val1, val2);
            // printf("%d %d\n", com_type, cont_type);
            int num_str = 0;

            char *data_str = strdup(find_dat_str(filename, cont_name, &num_str));
            database_processing(data_str, num_str, com_type, cont_type, val1, val2);
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
    // printf("%s\n", command);
    //  обработка команд и типов
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
    else
    {
        error = 1;
    }
    *cont_type = *com_type / 10;
    return error;
}

char *find_dat_str(char *file_name, char *cont_name, int *num_str)
{
    FILE *file;
    char *str = "NULL";
    int i = 0;
    if ((file = fopen(file_name, "r")) != NULL)
    {
        while (!feof(file))
        {
            char buff[MAX_LEN_FILE_STR];
            fgets(buff, MAX_LEN_FILE_STR, file);
            char *buff2 = strdup(buff);
            char *cur = strtok(buff, " ");
            if (strcmp(cur, cont_name) == 0)
            {

                str = strdup(buff2);
                break;
            }
            i++;
        }
        fclose(file);
    }

    *num_str = i;
    return str;
}

void database_processing(char *str, int num_str, int com_type, int cont_type, char *val1, char *val2)
{
    if (strcmp(str, "NULL") != 0)
    {
        char new_db_str[MAX_LEN_STR] = "";

        char *token = strtok(str, " ");
        strcat(new_db_str, token);
        strcat(new_db_str, " ");
        token = strtok(NULL, " ");
        strcat(new_db_str, token);
        strcat(new_db_str, " ");
        int str_cont_type;

        // проверка типов конейнеров
        if (strcmp(token, "set") == 0)
            str_cont_type = SET;
        else if (strcmp(token, "stack") == 0)
            str_cont_type = STACK;
        else if (strcmp(token, "queue") == 0)
            str_cont_type = QUEUE;
        else if (strcmp(token, "hashmap") == 0)
            str_cont_type = HASHMAP;
        // обработка команды
        if (str_cont_type == cont_type && token != NULL)
        {

            if (cont_type == SET)
            {
                set *myset = set_init();
                while ((token = strtok(NULL, " ")) != NULL)
                {
                    if (token[strlen(token) - 1] == '\n')
                        token[strlen(token) - 2] = '\0';
                    add(myset, token);
                }
                switch (com_type)
                {
                case SADD:
                    add(myset, val1);
                    break;
                case SREM:
                    rem(myset, val1);
                    break;
                case SISMEMBER:
                    printf("%d", is_member(*myset, val1));
                    break;

                default:
                    printf("error");
                    break;
                }

                for (int i = 0; i < SIZE; i++)
                {
                    node_of_set *cur = myset->items[i];
                    while (cur != NULL)
                    {
                        strcat(new_db_str, cur->data);

                        strcat(new_db_str, " ");
                        cur = cur->next;
                    }
                }
                strcat(new_db_str, "\n");
                printf("%s", new_db_str);
            }

            else if (cont_type == STACK)
            {
                stack *mystack = stack_init();
                while ((token = strtok(NULL, " ")) != NULL)
                {
                    if (token[strlen(token) - 1] == '\n')
                        token[strlen(token) - 2] = '\0';
                    push(mystack, token);
                }
                switch (com_type)
                {
                case SPUSH:
                    push(mystack, val1);
                    break;
                case SPOP:
                    printf("%s", pop(mystack));
                    break;

                default:
                    printf("error");
                    break;
                }
                stack *cur = mystack->head;
                char *datas[MAX_LEN_STR];
                int count = 0;
                while (cur != NULL)
                {
                    datas[count] = strdup(cur->data);
                    cur = cur->prev;
                    count++;
                }
                for (int j = count - 1; j >= 0; j--)
                {
                    strcat(new_db_str, datas[j]);

                    strcat(new_db_str, " ");
                }
                strcat(new_db_str, "\n");
                printf("%s", new_db_str);
            }

            else if (cont_type == QUEUE)
            {
                queue *myqueue = queue_init();
                while ((token = strtok(NULL, " ")) != NULL)
                {
                    if (token[strlen(token) - 1] == '\n')
                        token[strlen(token) - 2] = '\0';
                    enqueue(myqueue, token);
                }
                switch (com_type)
                {
                case QPUSH:
                    enqueue(myqueue, val1);
                    break;
                case QPOP:
                    printf("%s", dequeue(myqueue));
                    break;

                default:
                    printf("error");
                    break;
                }
                while (myqueue->front != NULL)
                {
                    strcat(new_db_str, myqueue->front->data);

                    strcat(new_db_str, " ");
                    myqueue->front = myqueue->front->next;
                }
                strcat(new_db_str, "\n");
                printf("%s", new_db_str);
            }

            else if (cont_type == HASHMAP)
            {
                hashmap *mymap = map_init();
                int i = 0;
                char *k = "NULL";
                char *v = "NULL";
                while ((token = strtok(NULL, " ")) != NULL)
                {
                    if (token[strlen(token) - 1] == '\n')
                        token[strlen(token) - 2] = '\0';
                    if (i % 2 == 0)
                        k = strdup(token);
                    else
                    {
                        v = strdup(token);
                        // printf("%s", k);
                        hset(mymap, k, v);
                    }
                    i++;
                }
                switch (com_type)
                {

                case HSET:
                    hset(mymap, val1, val2);
                    break;
                case HDEL:
                    del(mymap, val1);
                    break;
                case HGET:
                    printf("%s", get(*mymap, val1));
                    break;

                default:
                    printf("error");
                    break;
                }
                for (int i = 0; i < SIZE; i++)
                {
                    node_of_map *cur = mymap->items[i];
                    while (cur != NULL)
                    {
                        strcat(new_db_str, cur->key);

                        strcat(new_db_str, " ");
                        strcat(new_db_str, cur->val);

                        strcat(new_db_str, " ");
                        cur = cur->next;
                    }
                }
                strcat(new_db_str, "\n");
                printf("%s", new_db_str);
            }
        }
    }
}
