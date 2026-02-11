#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "lookup-table.h"
#include <ctype.h>
#include "hashmap.h"

int first_pass(char *filePath, HashMap *labels)
{

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    u_int16_t LC = 0;
    u_int16_t line_number = 1;

    fp = fopen(filePath, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char *comma_tokens[3];
        char *instruction_tokens[3];
        char *tmp;
        remove_comments(line);
        line = trimwhitespace(line);
        if (line[0] == '\0')
        {
            line_number++;
            continue;
        }

        int comma_tokens_count = tokenize_line(line, comma_tokens, ',');
        if (comma_tokens_count == -1 || comma_tokens_count > 2)
        {
            printf("error in line %d (most likely because of a redundant ',' ) ", line_number);
            return -1;
        }
        else if (comma_tokens_count == 1)
        {
            tmp = comma_tokens[0];
        }
        else if (comma_tokens_count == 2)
        {
            if (is_valid_label(comma_tokens[0]) != 0)
            {
                printf("label in line %d is not valid", line_number);
                return -1;
            }
            insert(labels, comma_tokens[0], LC);

            tmp = comma_tokens[1];
        }

        if (strstr(tmp, "ORG") != NULL)
        {
            tmp = trimwhitespace(tmp);
            int instruction_tokens_count = tokenize_line(tmp, instruction_tokens, ' ');
            if (instruction_tokens_count == -1)
            {
                printf("error in line %d", line_number);
                return -1;
            }
            else if (instruction_tokens_count == 1)
            {
                printf("error in line %d ORG needs an address", line_number);
                return -1;
            }
            else if (instruction_tokens_count == 3)
            {
                printf("error in line %d ORG has too many arguments", line_number);
                return -1;
            }
            if (isnumber(instruction_tokens[1]) != 0)
            {
                printf("error in line %d ORG address has to be a positive number", line_number);
                return -1;
            }
            int address = atoi(instruction_tokens[1]);
            if (address < 0)
            {
                printf("error in line %d ORG address has to be positive number", line_number);
                return -1;
            }
            LC = address - 1;
        }
        printf("LC:%d\n", LC);

        LC++;
        line_number++;
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s", line);
    }

    fclose(fp);
    // if (line)
    //     free(line);
    return 0;
}
