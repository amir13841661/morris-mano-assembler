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
                printf("error in line %d invalid instruction format", line_number);
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

int second_pass(char *filepath, HashMap *labels, char *outputFilename)
{

    FILE *fp, *fout;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    u_int16_t LC = 0;
    u_int16_t line_number = 1;
    u_int16_t memory = 0;

    fp = fopen(filepath, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    fout = fopen(outputFilename, "w");
    if (fout == NULL)
    {
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        int is_pseudo = 0;
        char *comma_tokens[3];
        char *instruction_tokens[3];
        char *tmp;
        int instruction_tokens_count;
        remove_comments(line);
        line = trimwhitespace(line);
        if (line[0] == '\0')
        {
            line_number++;
            continue;
        }

        int comma_tokens_count = tokenize_line(line, comma_tokens, ',');
        if (comma_tokens_count == 1)
        {
            tmp = comma_tokens[0];
        }
        else if (comma_tokens_count == 2)
        {
            tmp = comma_tokens[1];
        }
        tmp = trimwhitespace(tmp);
        instruction_tokens_count = tokenize_line(tmp, instruction_tokens, ' ');

        if (instruction_tokens_count == -1)
        {
            printf("error in line %d", line_number);
            return -1;
        }
        else if (instruction_tokens_count == 1)
        {
            if (strcmp(instruction_tokens[0], "END") == 0)
            {
                break;
            }
            memory = nonmemoryReferenceInstructions(instruction_tokens[0]);
            if (memory == 1)
            {
                printf("error in line %d invalid instruction format", line_number);
                return -1;
            }
        }
        else if (instruction_tokens_count == 2)
        {
            int holder;
            if (strcmp(instruction_tokens[0], "HEX") == 0)
            {
                char *endptr;
                memory = strtol(instruction_tokens[1], &endptr, 16);
                if (endptr == instruction_tokens[1] || *endptr != '\0')
                {
                    printf("error in line %d operand not a number", line_number);
                    return -1;
                }
            }
            else if (strcmp(instruction_tokens[0], "DEC") == 0)
            {
                char *endptr;
                memory = strtol(instruction_tokens[1], &endptr, 10);
                if (endptr == instruction_tokens[1] || *endptr != '\0')
                {
                    printf("error in line %d operand not a number", line_number);
                    return -1;
                }
            }
            else if (strcmp(instruction_tokens[0], "ORG") == 0)
            {
                char *endptr;
                int address = strtol(instruction_tokens[1], &endptr, 10);
                if (endptr == instruction_tokens[1] || *endptr != '\0')
                {
                    printf("error in line %d operand not a number", line_number);
                    return -1;
                }
                LC = address - 1;
                is_pseudo = 1;
            }
            else if ((holder = memoryReferenceInstructions(instruction_tokens[0])) != 1)
            {
                char *endptr;
                int address = strtol(instruction_tokens[1], &endptr, 10);
                if (endptr == instruction_tokens[1] || *endptr != '\0')
                {
                    if ((address = search(labels, instruction_tokens[1])) == -1)
                    {
                        printf("error in line %d operand not valid", line_number);
                        return -1;
                    }
                }
                memory = holder | address;
            }
            else
            {
                printf("error in line %d invalid instruction format", line_number);
                return -1;
            }
        }
        else if (instruction_tokens_count == 3)
        {
            int holder;

            if (strcmp(instruction_tokens[2], "I") != 0)
            {
                printf("error in line %d invalid instruction format", line_number);
                return -1;
            }
            if ((holder = memoryReferenceInstructions(instruction_tokens[0])) != 1)
            {
                char *endptr;
                int address = strtol(instruction_tokens[1], &endptr, 10);
                if (endptr == instruction_tokens[1] || *endptr != '\0')
                {
                    if ((address = search(labels, instruction_tokens[1])) == -1)
                    {
                        printf("error in line %d operand not valid", line_number);
                        return -1;
                    }
                }
                memory = holder | address | 0b1000000000000000;
            }
            else
            {
                printf("error in line %d invalid instruction format", line_number);
                return -1;
            }
        }

        printf("%d\n", memory);

        if (!is_pseudo)
        {
            // Write to file: [Address in 3 hex digits] [Data in 4 hex digits]
            fprintf(fout, "%03X %04X\n", (LC & 0xFFF), memory);
        }

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