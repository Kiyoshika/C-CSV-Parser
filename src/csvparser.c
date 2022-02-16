#include "csvparser.h"

// internal function
// counts columns based on delimiter
// used to size the tokens array within csv_parse_line
size_t csv_count_columns(const char* line, char delim)
{
    size_t delim_count = 0;

    for (size_t i = 0; i < strlen(line); ++i)
        if (line[i] == delim)
            delim_count++;

    return delim_count + 1; // + 1 since no delimiter at end of string
}

// parses a line of CSV and stores parsed values into tokens
// tokens must be free'd by the client
// TODO: add support for delimiters within quotes to avoid parsing issues
// returns number of tokens that were extracted. can be used by client when freeing memory
size_t csv_parse_line(const char* line, char*** tokens, char delim)
{
    size_t current_col = 0;
    char* parsed_value = NULL;
    size_t parsed_value_alloc_size = 0;

    size_t delim_count = csv_count_columns(line, delim);

    (*tokens) = malloc(sizeof(char*) * delim_count);

    for (size_t i = 0; i < strlen(line); ++i)
    {
        if (line[i] != delim)
        {
            if (parsed_value == NULL)
            {
                parsed_value = calloc(11, 1); // allocate 10 characters + \0 initially
                strncat(parsed_value, &line[i], 1);
                parsed_value_alloc_size = 10;
            }
            else
            {
                if (strlen(parsed_value) > parsed_value_alloc_size)
                {
                    parsed_value_alloc_size *= 2;
                    parsed_value = realloc(parsed_value, parsed_value_alloc_size + 1);
                }

                strncat(parsed_value, &line[i], 1);
            }
        }
        else if (line[i] == delim)
        {
            (*tokens)[current_col] = strdup(parsed_value);
            free(parsed_value);
            parsed_value = NULL;
            parsed_value_alloc_size = 0;
            current_col++;
        }
    }

    // no delimiter at end of string so we check if parsed_value still contains content
    if (strlen(parsed_value) > 0)
    {
        (*tokens)[current_col] = strdup(parsed_value);
        free(parsed_value);
        parsed_value = NULL;
    }

    return delim_count;
}