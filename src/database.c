#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
            FILE *check_file;
            check_file = fopen(filename, "a+");
            // if (check_file != NULL)
            fclose(check_file);

            break;
        case 'q':
            // вызов функции коротая определяет порядок действий с БД
            strcpy(query, optarg);
            char *val1;
            char *val2;
            char *cont_name;
            int com_type = 0, cont_type = 0;
            query_parsing(query, &com_type, &cont_type, &cont_name, &val1, &val2);

            int num_str = 0;
            int file_len = 0;

            // копирование строки с найденным контейнером
            char *data_str = strdup(find_dat_str(filename, cont_name, &num_str, &file_len));
            if (num_str == -1)
            {
                strcat(data_str, cont_name);
                strcat(data_str, " ");
                switch (cont_type)
                {
                case SET:
                    strcat(data_str, "set");
                    strcat(data_str, " ");
                    break;
                case STACK:
                    strcat(data_str, "stack");
                    strcat(data_str, " ");
                    break;
                case QUEUE:
                    strcat(data_str, "queue");
                    strcat(data_str, " ");
                    break;
                case HASHMAP:
                    strcat(data_str, "hashmap");
                    strcat(data_str, " ");
                    break;

                default:
                    break;
                }
            }
            upd_file(filename, file_len, data_str, num_str, com_type, cont_type, val1, val2);

            break;
        default:
            break;
        }
    }
    return error;
}

void upd_file(char *filename, int file_len, char *data_str, int num_str, int com_type, int cont_type, char *val1, char *val2)
{
    char *new_db_str = strdup(database_processing(data_str, num_str, com_type, cont_type, val1, val2));
    FILE *file;
    FILE *buff_file = fopen("buff.dat", "w");

    if ((file = fopen(filename, "r")) != NULL)
    {

        int is_found = 0;
        int i = 0;
        while (i != file_len)
        {
            char buff[MAX_LEN_FILE_STR];
            fgets(buff, MAX_LEN_FILE_STR, file);

            if (i != num_str)
            {
                if (strcmp(buff, "end_of_file\n") != 0)
                {
                    fprintf(buff_file, "%s", buff);
                }
            }
            else
            {
                if (new_db_str[0] != 0)
                    fprintf(buff_file, "%s\n", new_db_str);
                is_found = 1;
            }
            i++;
        }
        fclose(file);
        if (num_str == -1)
        {
            if (new_db_str[0] != 0)
                fprintf(buff_file, "%s\n", new_db_str);
        }
        fprintf(buff_file, "%s\n", "end_of_file");
    }
    remove(filename);
    rename("buff.dat", filename);
    fclose(buff_file);
}

int query_parsing(char *query, int *com_type, int *cont_type, char **cont_name, char **val1, char **val2)
{
    int error = 0;
    char *command = strtok(query, " ");
    *cont_name = strtok(NULL, " ");
    *val1 = strtok(NULL, " ");
    *val2 = strtok(NULL, " ");
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

char *find_dat_str(char *file_name, char *cont_name, int *num_str, int *file_len)
{
    FILE *file;
    char *str = "";
    int i = -1;
    int j = 0;
    if ((file = fopen(file_name, "r")) != NULL)
    {
        while (!feof(file))
        {
            char buff[MAX_LEN_FILE_STR];
            fgets(buff, MAX_LEN_FILE_STR, file);
            char *buff2 = strdup(buff);
            char *cur;

            if (strlen(buff) > 0)
            {
                cur = strtok(buff, " ");
            }
            if (cur != NULL)
            {
                if (strcmp(cur, cont_name) == 0)
                {

                    str = strdup(buff2);
                    i = j;
                }
            }

            j++;
        }
        fclose(file);
    }
    *file_len = j - 1;
    *num_str = i;
    return str;
}

char *database_processing(char *str, int num_str, int com_type, int cont_type, char *val1, char *val2)
{
    char new_db_str[MAX_LEN_STR] = "";
    if (str != NULL)
    {
    }
    char *old_db_str = strdup(str);
    //  добавление в строку названия и типа контейнера
    char *token;
    token = strtok(str, " ");
    strcat(new_db_str, token);
    strcat(new_db_str, " ");
    token = strtok(NULL, " ");
    strcat(new_db_str, token);
    strcat(new_db_str, " ");

    // проверка типов конейнеров
    int str_cont_type;
    if (strcmp(token, "set") == 0)
        str_cont_type = SET;
    else if (strcmp(token, "stack") == 0)
        str_cont_type = STACK;
    else if (strcmp(token, "queue") == 0)
        str_cont_type = QUEUE;
    else if (strcmp(token, "hashmap") == 0)
        str_cont_type = HASHMAP;
    else
        str_cont_type = -1;
    if (str_cont_type == cont_type)
    {
        // копирование элементов контейнера в массив
        char *datas[MAX_LEN_STR];
        int elems_cnt = 0;
        while ((token = strtok(NULL, " ")) != NULL)
        {
            if (token[strlen(token) - 1] == '\n')
                token[strlen(token) - 1] = '\0';

            datas[elems_cnt] = strdup(token);

            elems_cnt++;
        }

        // обработка команды

        if (cont_type == SET)
        {
            upd_set(new_db_str, com_type, val1, datas, elems_cnt);
        }

        else if (cont_type == STACK)
        {
            upd_stack(new_db_str, com_type, val1, datas, elems_cnt);
        }

        else if (cont_type == QUEUE)
        {
            upd_queue(new_db_str, com_type, val1, datas, elems_cnt);
        }

        else if (cont_type == HASHMAP)
        {
            upd_hashmap(new_db_str, com_type, val1, val2, datas, elems_cnt);
        }

        else

            memset(new_db_str, 0, strlen(new_db_str));
        for (int i = 0; i < elems_cnt; i++)
        {
            free(datas[i]);
        }
        char *s = strdup(new_db_str);

        return s;
    }
    else
    {
        if (old_db_str[strlen(old_db_str) - 1] == '\n')
            old_db_str[strlen(old_db_str) - 1] = '\0';
        return old_db_str;
    }
}

void upd_set(char *new_db_str, int com_type, char *val1, char **datas, char elems_cnt)
{
    set *myset = set_init();
    for (int i = 0; i < elems_cnt; i++)
    {
        add(myset, datas[i]);
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
        printf("%d\n", is_member(*myset, val1));
        break;

    default:
        printf("error\n");
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

    new_db_str[strlen(new_db_str) - 1] = '\0';
    if (is_empty_set(*myset))
        memset(new_db_str, 0, strlen(new_db_str));
    set_clear(myset);
}

void upd_stack(char *new_db_str, int com_type, char *val1, char **datas, char elems_cnt)
{
    stack *mystack = stack_init();

    for (int i = 0; i < elems_cnt; i++)
    {
        push(mystack, datas[i]);
    }

    switch (com_type)
    {
    case SPUSH:
        push(mystack, val1);
        break;
    case SPOP:
        printf("%s\n", pop(mystack));
        break;

    default:
        printf("error\n");
        break;
    }
    char *stack_datas[MAX_LEN_STR];
    int sd_cnt = 0;
    stack *cur = mystack->head;
    while (cur != NULL)
    {
        stack_datas[sd_cnt] = strdup(cur->data);

        cur = cur->prev;
        sd_cnt++;
    }
    for (int i = sd_cnt - 1; i >= 0; i--)
    {
        strcat(new_db_str, stack_datas[i]);
        strcat(new_db_str, " ");
    }

    new_db_str[strlen(new_db_str) - 1] = '\0';
    if (is_empty_stack(mystack))
        memset(new_db_str, 0, strlen(new_db_str));
    stack_clear(mystack);
}

void upd_queue(char *new_db_str, int com_type, char *val1, char **datas, char elems_cnt)
{
    queue *myqueue = queue_init();
    for (int i = 0; i < elems_cnt; i++)
    {
        enqueue(myqueue, datas[i]);
    }

    switch (com_type)
    {
    case QPUSH:
        enqueue(myqueue, val1);
        break;
    case QPOP:
        printf("%s\n", dequeue(myqueue));
        break;

    default:
        printf("error\n");
        break;
    }
    queue *cur = myqueue->front;
    while (cur != NULL)
    {
        strcat(new_db_str, cur->data);

        strcat(new_db_str, " ");
        cur = cur->next;
    }

    new_db_str[strlen(new_db_str) - 1] = '\0';
    if (is_empty_queue(myqueue))
        memset(new_db_str, 0, strlen(new_db_str));
    queue_clear(myqueue);
}

void upd_hashmap(char *new_db_str, int com_type, char *val1, char *val2, char **datas, char elems_cnt)
{

    hashmap *mymap = map_init();

    char *k;
    char *v;
    for (int i = 0; i < elems_cnt; i++)
    {
        if (i % 2 == 0)
            k = strdup(datas[i]);
        else
        {
            v = strdup(datas[i]);
            hset(mymap, k, v);
        }
    }

    switch (com_type)
    {

    case HSET:
        if (val2 != NULL)
            hset(mymap, val1, val2);
        break;
    case HDEL:
        del(mymap, val1);
        break;
    case HGET:
        printf("%s\n", get(*mymap, val1));
        break;

    default:
        printf("error\n");
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

    new_db_str[strlen(new_db_str) - 1] = '\0';
    if (is_empty_map(mymap))
        memset(new_db_str, 0, strlen(new_db_str));
    map_clear(mymap);
}
