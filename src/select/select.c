#include "select/select.h"
#include "read/read.h"
#include "free/free.h"
#include "cast/cast.h"

void csv_select_by_name(const char* filename, char** column_names, size_t n_columns, char**** data, size_t (*data_dims)[2], char delim)
{
    char** current_column = NULL;
    size_t rows;
    bool allocated = false;

    for (size_t c = 0; c < n_columns; ++c)
    {
        csv_read_column_by_name(filename, column_names[c], &current_column, &rows, delim);

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

void csv_select_by_name_as_float(const char* filename, char** column_names, size_t n_columns, float*** data, size_t (*data_dims)[2], char delim)
{
    char*** s_data = NULL;
    csv_select_by_name(filename, column_names, n_columns, &s_data, data_dims, delim);
    csv_data_to_float(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
}

void csv_select_by_name_as_int(const char* filename, char** column_names, size_t n_columns, int*** data, size_t (*data_dims)[2], char delim)
{
    char*** s_data = NULL;
    csv_select_by_name(filename, column_names, n_columns, &s_data, data_dims, delim);
    csv_data_to_int(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
}

void csv_select_by_index(const char* filename, size_t* column_indices, size_t n_columns, char**** data, size_t (*data_dims)[2], char delim, bool has_headers)
{
    char** current_column = NULL;
    size_t rows;
    bool allocated = false;

    for (size_t c = 0; c < n_columns; ++c)
    {
        csv_read_column_by_index(filename, column_indices[c], &current_column, &rows, delim, has_headers);

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

void csv_select_by_index_as_float(const char* filename, size_t* column_indices, size_t n_columns, float*** data, size_t (*data_dims)[2], char delim, bool has_headers)
{
    char*** s_data = NULL;
    csv_select_by_index(filename, column_indices, n_columns, &s_data, data_dims, delim, has_headers);
    csv_data_to_float(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
}

void csv_select_by_index_as_int(const char* filename, size_t* column_indices, size_t n_columns, int*** data, size_t (*data_dims)[2], char delim, bool has_headers)
{
    char*** s_data = NULL;
    csv_select_by_index(filename, column_indices, n_columns, &s_data, data_dims, delim, has_headers);
    csv_data_to_int(s_data, *data_dims, data);
    csv_free(&s_data, *data_dims);
}