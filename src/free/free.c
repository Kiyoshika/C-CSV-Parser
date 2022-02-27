#include "free/free.h"

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