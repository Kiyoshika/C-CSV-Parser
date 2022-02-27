#include "csvinternal.h"
#include "ignore/ignore.h"
#include "read/read.h"
#include "free/free.h"
#include "cast/cast.h"

int string_cmp(const void* a, const void* b)
{
    return strcmp(*(char**)a, *(char**)b);
}

int size_t_cmp(const void* a, const void* b)
{
    const size_t _a = *(size_t*)a;
    const size_t _b = *(size_t*)b;

    if (_a == _b)
        return 0;
    else if (_a > _b)
        return 1;
    return -1;
}

void csv_ignore_by_name(const char* filename, char** column_names, size_t n_columns, char**** data, size_t (*data_dims)[2], char delim)
{
    char** current_column = NULL;
    size_t rows;
    bool allocated = false;

    // read first line in file to count the total columns
    char** all_columns = NULL;
    size_t total_column_count = csv_get_column_names(filename, delim, &all_columns);

    // sort columns for quick binary searching
    qsort(column_names, n_columns, sizeof(char*), &string_cmp);

    size_t current_iter = 0;
    void* search_value;

    for (size_t c = 0; c < total_column_count; ++c)
    {
        search_value = bsearch(&all_columns[c], column_names, n_columns, sizeof(char*), &string_cmp);
        // checking if the column is NOT found since we are trying to ignore it
        if (search_value == NULL)
        {
            csv_read_column_by_name(filename, all_columns[c], &current_column, &rows, delim);

            // allocate memory for user's data when number of rows is known
            if (!allocated)
            {
                (*data) = calloc(rows, sizeof(char**));
                for (size_t i = 0; i < rows; ++i)
                    (*data)[i] = calloc(total_column_count - n_columns, sizeof(char*));
                (*data_dims)[0] = rows;
                (*data_dims)[1] = total_column_count - n_columns;
                allocated = true;
            }

            // copy data from column into user's data and free it back
            for (size_t r = 0; r < rows; ++r)
                (*data)[r][current_iter] = strdup(current_column[r]);
            csv_free_column(&current_column, rows);

            current_iter++;
        }
    }
    csv_free_column(&all_columns, total_column_count);
}

void csv_ignore_by_name_as_float(const char* filename, char** column_names, size_t n_columns, float*** data, size_t (*data_dims)[2], char delim)
{
    char*** s_data = NULL;
    csv_ignore_by_name(filename, column_names, n_columns, &s_data, data_dims, delim);
    csv_data_to_float(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
}

void csv_ignore_by_name_as_int(const char* filename, char** column_names, size_t n_columns, int*** data, size_t (*data_dims)[2], char delim)
{
    char*** s_data = NULL;
    csv_ignore_by_name(filename, column_names, n_columns, &s_data, data_dims, delim);
    csv_data_to_int(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
}

void csv_ignore_by_index(const char* filename, size_t* column_indices, size_t n_columns, char**** data, size_t (*data_dims)[2], char delim, bool has_headers)
{
    char** current_column = NULL;
    size_t rows;
    bool allocated = false;

    // read first line in file to count the total columns
    // then create array to store all columns
    char** all_columns = NULL;
    size_t total_column_count = csv_get_column_names(filename, delim, &all_columns);
    csv_free_column(&all_columns, total_column_count);
    size_t* all_column_indices = calloc(total_column_count, sizeof(size_t));
    for (size_t i = 0; i < total_column_count; ++i)
        all_column_indices[i] = i;

    // sort columns for quick binary searching
    qsort(column_indices, n_columns, sizeof(size_t), &size_t_cmp);

    size_t current_iter = 0;
    void* search_value;

    for (size_t c = 0; c < total_column_count; ++c)
    {
        search_value = bsearch(&all_column_indices[c], column_indices, n_columns, sizeof(size_t), &size_t_cmp);
        // checking if the column is NOT found since we are trying to ignore it
        if (search_value == NULL)
        {
            csv_read_column_by_index(filename, all_column_indices[c], &current_column, &rows, delim, has_headers);

            // allocate memory for user's data when number of rows is known
            if (!allocated)
            {
                (*data) = calloc(rows, sizeof(char**));
                for (size_t i = 0; i < rows; ++i)
                    (*data)[i] = calloc(total_column_count - n_columns, sizeof(char*));
                (*data_dims)[0] = rows;
                (*data_dims)[1] = total_column_count - n_columns;
                allocated = true;
            }

            // copy data from column into user's data and free it back
            for (size_t r = 0; r < rows; ++r)
                (*data)[r][current_iter] = strdup(current_column[r]);
            csv_free_column(&current_column, rows);

            current_iter++;
        }
    }
    free(all_column_indices);
}

void csv_ignore_by_index_as_float(const char* filename, size_t* column_indices, size_t n_columns, float*** data, size_t (*data_dims)[2], char delim, bool has_headers)
{
    char*** s_data = NULL;
    csv_ignore_by_index(filename, column_indices, n_columns, &s_data, data_dims, delim, has_headers);
    csv_data_to_float(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
}

void csv_ignore_by_index_as_int(const char* filename, size_t* column_indices, size_t n_columns, int*** data, size_t (*data_dims)[2], char delim, bool has_headers)
{
    char*** s_data = NULL;
    csv_ignore_by_index(filename, column_indices, n_columns, &s_data, data_dims, delim, has_headers);
    csv_data_to_int(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
}