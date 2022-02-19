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

// internal function
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
        // e.g in the case of val1,val2, (trailing comma at end)
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

void csv_read(const char* filename, char**** data, char delim, size_t (*data_dims)[2], bool has_headers)
{
    FILE* file = fopen(filename, "r");
    if (file != NULL)
    {
        char* line = NULL;
        char **tokens = NULL;
        size_t len = 0;
        size_t read = 0;

        // start with allocating memory for 10 lines, then double each time capacity is reached
        size_t row_allocation_size = 10;
        (*data) = calloc(row_allocation_size, sizeof(char**));

        size_t current_row = 0;
        size_t n_tokens;

        bool counted_columns = false;

        while ((read = getline(&line, &len, file)) != -1)
        {
            // count the columns and store them into first index in data_dims
            if (!counted_columns)
            {
                (*data_dims)[1] = csv_count_columns(line, delim);
                counted_columns = true;
            }

            // skip header line if present
            if (has_headers)
            {
                has_headers = false;
                continue;
            }

            n_tokens = csv_parse_line(line, &tokens, delim);
            (*data)[current_row] = malloc(sizeof(char*) * n_tokens);
            for (size_t i = 0; i < n_tokens; ++i)
            {
                // duplicate a copy of tokens[i] into data then free it so we can use tokens on next iteration
                (*data)[current_row][i] = strdup(tokens[i]);
                free(tokens[i]);
                tokens[i] = NULL;
            }

            current_row++;
            if (current_row >= row_allocation_size)
            {
                row_allocation_size *= 2;
                (*data) = realloc((*data), sizeof(char**) * row_allocation_size);
            }

            // free tokens to use them on next iteration
            free(tokens);
            tokens = NULL;
        }
        free(line);
        fclose(file);

        // store row count into 0th index in data_dims
        (*data_dims)[0] = current_row;
    }
    else
    {
        printf("File not found!\n");
        exit(-1);
    }
}

void csv_read_column_by_index(const char* filename, size_t column_index, char*** data, char delim, size_t* data_rows, bool has_headers)
{
    FILE* file = fopen(filename, "r");
    if (file != NULL)
    {
        char* line = NULL;
        char **tokens = NULL;
        size_t len = 0;
        size_t read = 0;

        // start with allocating memory for 10 lines, then double each time capacity is reached
        size_t row_allocation_size = 10;
        (*data) = calloc(row_allocation_size, sizeof(char**));

        size_t current_row = 0;
        size_t n_tokens;

        while ((read = getline(&line, &len, file)) != -1)
        {

            // skip header line if present
            if (has_headers)
            {
                has_headers = false;
                continue;
            }

            n_tokens = csv_parse_line(line, &tokens, delim);
            (*data)[current_row] = strdup(tokens[column_index]);
            for (size_t i = 0; i < n_tokens; ++i)
            {
                free(tokens[i]);
                tokens[i] = NULL;
            }

            current_row++;
            if (current_row >= row_allocation_size)
            {
                row_allocation_size *= 2;
                (*data) = realloc((*data), sizeof(char**) * row_allocation_size);
            }

            // free tokens to use them on next iteration
            free(tokens);
            tokens = NULL;
        }
        free(line);
        fclose(file);

        // store row count
        *data_rows = current_row;
    }
    else
    {
        printf("File not found!\n");
        exit(-1);
    }
}

void csv_read_column_by_name(const char* filename, const char* column_name, char*** data, char delim, size_t* data_rows)
{
    FILE* file = fopen(filename, "r");
    if (file != NULL)
    {
        char** tokens = NULL;
        char* line = NULL;
        size_t len = 0;
        size_t n_tokens;

        getline(&line, &len, file);
        n_tokens = csv_parse_line(line, &tokens, delim);

        for (size_t i = 0; i < n_tokens; ++i)
            if (strncmp(tokens[i], column_name, strlen(column_name)) == 0)
                csv_read_column_by_index(filename, i, data, delim, data_rows, true);

        free(line);
        for (size_t i = 0; i < n_tokens; ++i)
            free(tokens[i]);
        free(tokens);
    }
    else
    {
        printf("File not found!\n");
        exit(-1);
    }
}

void csv_free(char**** data, size_t data_dims[2])
{
    for (size_t i = 0; i < data_dims[0]; ++i)
    {
        for (size_t j = 0; j < data_dims[1]; ++j)
        {
            free((*data)[i][j]);
            (*data)[i][j] = NULL;
        }
        free((*data)[i]);
        (*data)[i] = NULL;
    }
    free((*data));
    (*data) = NULL;
}

void csv_free_column(char*** data, size_t data_rows)
{
    for (size_t i = 0; i < data_rows; ++i)
    {
        free((*data)[i]);
        (*data)[i] = NULL;
    }
    free(*data);
    *data = NULL;
}