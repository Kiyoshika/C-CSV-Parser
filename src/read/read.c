#include "csvinternal.h"
#include "read/read.h"
#include "cast/cast.h"
#include "free/free.h"

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

            n_tokens = csv_parse_line(line, delim, &tokens);
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

void csv_read_column_by_index(const char* filename, size_t column_index, char*** data, size_t* data_rows, char delim, bool has_headers)
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

            n_tokens = csv_parse_line(line, delim, &tokens);
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

void csv_read_column_by_index_as_float(const char* filename, size_t column_index, float** data, size_t* data_rows, char delim, bool has_headers)
{
    char** s_data = NULL;
    csv_read_column_by_index(filename, column_index, &s_data, data_rows, delim, has_headers);
    csv_column_to_float(s_data, *data_rows, data);
    csv_free_column(&s_data, *data_rows);
}

void csv_read_column_by_index_as_int(const char* filename, size_t column_index, int** data, size_t* data_rows, char delim, bool has_headers)
{
    char** s_data = NULL;
    csv_read_column_by_index(filename, column_index, &s_data, data_rows, delim, has_headers);
    csv_column_to_int(s_data, *data_rows, data);
    csv_free_column(&s_data, *data_rows);
}

void csv_read_column_by_name(const char* filename, const char* column_name, char*** data, size_t* data_rows, char delim)
{
    FILE* file = fopen(filename, "r");
    if (file != NULL)
    {
        char** tokens = NULL;
        char* line = NULL;
        size_t len = 0;
        size_t n_tokens;

        getline(&line, &len, file);
        n_tokens = csv_parse_line(line, delim, &tokens);

        for (size_t i = 0; i < n_tokens; ++i)
            if (strncmp(tokens[i], column_name, strlen(column_name)) == 0)
                csv_read_column_by_index(filename, i, data, data_rows, delim, true);

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

void csv_read_column_by_name_as_float(const char* filename, const char* column_name, float** data, size_t* data_rows, char delim)
{
    char** s_data = NULL;
    csv_read_column_by_name(filename, column_name, &s_data, data_rows, delim);
    csv_column_to_float(s_data, *data_rows, data);
    csv_free_column(&s_data, *data_rows);
}

void csv_read_column_by_name_as_int(const char* filename, const char* column_name, int** data, size_t* data_rows, char delim)
{
    char** s_data = NULL;
    csv_read_column_by_name(filename, column_name, &s_data, data_rows, delim);
    csv_column_to_int(s_data, *data_rows, data);
    csv_free_column(&s_data, *data_rows);
}