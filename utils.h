#define _GNU_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_comments(char *line)
{
    char *tmp = line;

    while (*tmp != '#' && *tmp != '\0')
        tmp++;
    *tmp = '\0';
}

int tokenize_line(char *line, char *result[], char delimiter)
{
    char delim_str[2] = {delimiter, '\0'};
    char *token = strtok(line, delim_str);
    result[0] = token;
    int token_count = 0;

    while (token != NULL)
    {
        token_count++;
        if (token_count >= 3)
        {
            return -1;
        }
        // printf("got token %s", token);
        token = strtok(NULL, delim_str);
        result[token_count] = token;
    }
    return token_count;
}

char *trimwhitespace(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

int is_valid_label(char *str)
{
    str = trimwhitespace(str);

    size_t len = strlen(str);
    if (len == 0 || len > 64)
    {
        return -1;
    }

    if (!isalpha((unsigned char)*str) && *str != '_')
    {
        return -1;
    }

    while (*str != '\0')
    {
        if (!isalnum((unsigned char)*str) && *str != '_')
        {
            return -1;
        }
        str++;
    }

    return 0;
}

int isnumber(char *str)
{
    if (str == NULL || *str == '\0')
    {
        return -1;
    }

    char *tmp = str;

    if (*tmp == '-' || *tmp == '+')
    {
        tmp++;
    }

    if (*tmp == '\0')
    {
        return -1;
    }

    while (*tmp != '\0')
    {
        if (!isdigit((unsigned char)*tmp))
        {
            return -1;
        }
        tmp++;
    }

    return 0;
}