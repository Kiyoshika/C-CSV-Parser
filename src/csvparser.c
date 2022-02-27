#include "csvparser.h"

// internal function
// counts columns based on delimiter
// used to size the tokens array within csv_parse_line
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

// internal function
// parses a line of CSV and stores parsed values into tokens
// tokens must be free'd by the client
// returns number of tokens that were extracted. can be used by client when freeing memory
size_t csv_parse_line(const char* line, char*** tokens, char delim)
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

void csv_read(const char* filename, char**** data, size_t (*data_dims)[2], char delim, bool has_headers)
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

void csv_read_int(const char* filename, int*** data, size_t (*data_dims)[2], char delim, bool has_headers)
{
    char*** s_data = NULL;
    csv_read(filename, &s_data, data_dims, delim, has_headers);
    csv_data_to_int(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
}
void csv_read_float(const char* filename, float*** data, size_t (*data_dims)[2], char delim, bool has_headers)
{
    char*** s_data = NULL;
    csv_read(filename, &s_data, data_dims, delim, has_headers);
    csv_data_to_float(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
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

void csv_read_column_by_index_as_float(const char* filename, size_t column_index, float** data, char delim, size_t* data_rows, bool has_headers)
{
    char** s_data = NULL;
    csv_read_column_by_index(filename, column_index, &s_data, delim, data_rows, has_headers);
    csv_column_to_float(s_data, *data_rows, data);
    csv_free_column(&s_data, *data_rows);
}

void csv_read_column_by_index_as_int(const char* filename, size_t column_index, int** data, char delim, size_t* data_rows, bool has_headers)
{
    char** s_data = NULL;
    csv_read_column_by_index(filename, column_index, &s_data, delim, data_rows, has_headers);
    csv_column_to_int(s_data, *data_rows, data);
    csv_free_column(&s_data, *data_rows);
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

void csv_read_column_by_name_as_float(const char* filename, const char* column_name, float** data, char delim, size_t* data_rows)
{
    char** s_data = NULL;
    csv_read_column_by_name(filename, column_name, &s_data, delim, data_rows);
    csv_column_to_float(s_data, *data_rows, data);
    csv_free_column(&s_data, *data_rows);
}

void csv_read_column_by_name_as_int(const char* filename, const char* column_name, int** data, char delim, size_t* data_rows)
{
    char** s_data = NULL;
    csv_read_column_by_name(filename, column_name, &s_data, delim, data_rows);
    csv_column_to_int(s_data, *data_rows, data);
    csv_free_column(&s_data, *data_rows);
}

void csv_select_by_name(const char* filename, char** column_names, size_t n_columns, char**** data, char delim, size_t (*data_dims)[2])
{
    char** current_column = NULL;
    size_t rows;
    bool allocated = false;

    for (size_t c = 0; c < n_columns; ++c)
    {
        csv_read_column_by_name(filename, column_names[c], &current_column, delim, &rows);

        // allocate memory for user's data when number of rows is known
        if (!allocated)
        {
            (*data) = calloc(rows, sizeof(char**));
            for (size_t i = 0; i < rows; ++i)
                (*data)[i] = calloc(n_columns, sizeof(char*));
            allocated = true;
        }

        // copy data from column into user's data and free it back
        for (size_t r = 0; r < rows; ++r)
            (*data)[r][c] = strdup(current_column[r]);
        csv_free_column(&current_column, rows);
    }

    (*data_dims)[0] = rows;
    (*data_dims)[1] = n_columns;

}

void csv_data_to_int(char*** data, size_t data_dims[2], int*** int_data)
{
    // allocate necessary memory to store the integers
    *int_data = malloc(sizeof(int*) * data_dims[0]);
    for (size_t i = 0; i < data_dims[0]; ++i)
        (*int_data)[i] = malloc(sizeof(int) * data_dims[1]);

    // cast values from string to int
    char* end;
    for (size_t i = 0; i < data_dims[0]; ++i)
        for (size_t j = 0; j < data_dims[1]; ++j)
            (*int_data)[i][j] = strtol(data[i][j], &end, 10);
}

void csv_data_to_float(char*** data, size_t data_dims[2], float*** float_data)
{
    // allocate necessary memory to store the integers
    *float_data = malloc(sizeof(float*) * data_dims[0]);
    for (size_t i = 0; i < data_dims[0]; ++i)
        (*float_data)[i] = malloc(sizeof(float) * data_dims[1]);

    // cast values from string to int
    char* end;
    for (size_t i = 0; i < data_dims[0]; ++i)
        for (size_t j = 0; j < data_dims[1]; ++j)
            (*float_data)[i][j] = strtof(data[i][j], &end);
}

void csv_column_to_int(char** data, size_t data_rows, int** int_data)
{
    // allocate necessary memory to store the integers
    *int_data = malloc(sizeof(int) * data_rows);

    // cast values from string to int
    char* end;
    for (size_t i = 0; i < data_rows; ++i)
            (*int_data)[i] = strtol(data[i], &end, 10);
}

void csv_column_to_float(char** data, size_t data_rows, float** float_data)
{
    // allocate necessary memory to store the integers
    *float_data = malloc(sizeof(float) * data_rows);

    // cast values from string to int
    char* end;
    for (size_t i = 0; i < data_rows; ++i)
        (*float_data)[i] = strtof(data[i], &end);
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

void csv_free_int(int*** data, size_t data_rows)
{
    for (size_t i = 0; i < data_rows; ++i)
    {
        free((*data)[i]);
        (*data)[i] = NULL;
    }
    free((*data));
    (*data) = NULL;
}

void csv_free_float(float*** data, size_t data_rows)
{
    for (size_t i = 0; i < data_rows; ++i)
    {
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

void csv_free_column_int(int** data)
{
    free(*data);
    *data = NULL;
}

void csv_free_column_float(float** data)
{
    free(*data);
    *data = NULL;
}