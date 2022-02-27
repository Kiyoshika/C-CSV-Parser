#include "cast/cast.h"

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