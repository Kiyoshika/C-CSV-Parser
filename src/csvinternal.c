#include "csvinternal.h"

size_t csv_count_columns(const char* line, char delim)
{
    size_t delim_count = 0;
    bool inside_quotes = false;

    for (size_t i = 0; i < strlen(line); ++i)
    {
        if (line[i] == '\"')
            inside_quotes = !inside_quotes;

        if (line[i] == delim && !inside_quotes)
            delim_count++;
    }

    return delim_count + 1; // + 1 since no delimiter at end of string
}

size_t csv_parse_line(const char* line, char delim, char*** tokens)
{
    size_t current_col = 0;
    char* parsed_value = NULL;
    size_t parsed_value_alloc_size = 0;

    bool inside_quotes = false;

    size_t delim_count = csv_count_columns(line, delim);

    (*tokens) = malloc(sizeof(char*) * delim_count);

    for (size_t i = 0; i < strlen(line); ++i)
    {
        if (line[i] == '\"')
            inside_quotes = !inside_quotes;

        if (line[i] != delim || (line[i] == delim && inside_quotes))
        {
            if (parsed_value == NULL)
            {
                parsed_value = calloc(11, 1); // allocate 10 characters + \0 initially
                strncat(parsed_value, &line[i], 1);
                parsed_value_alloc_size = 10;
            }
            else
            {
                if (strlen(parsed_value) > parsed_value_alloc_size - 1)
                {
                    parsed_value_alloc_size *= 2;
                    parsed_value = realloc(parsed_value, parsed_value_alloc_size + 1);
                }

                strncat(parsed_value, &line[i], 1);
            }
        }
        else if (line[i] == delim && !inside_quotes)
        {
            if (parsed_value != NULL)
            {
                (*tokens)[current_col] = strdup(parsed_value);
                free(parsed_value);
                parsed_value = NULL;
            }
            else
                (*tokens)[current_col] = strdup("(null)");

            parsed_value_alloc_size = 0;
            current_col++;
        }
    }

    // no delimiter at end of string so we check if parsed_value still contains content
    if (parsed_value != NULL && strlen(parsed_value) > 0)
    {
        // remove trailing \n from input (unless it's the only remaining character left)
        // e.g. in the case of val1,val2, (trailing comma at end)
        if (strcmp(parsed_value, "\n") == 0)
        {
            (*tokens)[current_col] = strdup("(null)");
            free(parsed_value);
            parsed_value = NULL;
        }
        else
        {
            parsed_value[strcspn(parsed_value, "\n")] = 0;
            (*tokens)[current_col] = strdup(parsed_value);
            free(parsed_value);
            parsed_value = NULL;
        }
    }
    else if (parsed_value == NULL)
    {
        (*tokens)[current_col] = strdup("(null)");
    }

    return delim_count;
}

size_t csv_get_column_names(const char* filename, char delim, char*** columns)
{
    size_t column_count = 0;
    char* line = NULL;
    size_t len = 0;
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        exit(-1);
    }

    getline(&line, &len, file);
    column_count = csv_parse_line(line, delim, columns);
    free(line);
    fclose(file);
    return column_count;
}