#ifndef CSVPARSER_CAST_H
#define CSVPARSER_CAST_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @description Convert CSV data (char***) to integers (int**).
 * @param data A char*** pointer to data loaded with csv_read().
 * @param data_dims size_t[2] array specifying dimensions of the data with the 0th index counting the rows and 1st index counting the columns
 * @param int_data An int** pointer passed by address to allocate and store the casted integers from data.
 */
void csv_data_to_int(char*** data, size_t data_dims[2], int*** int_data);

/**
 * @description Convert CSV data (char***) to floats (float**).
 * @param data A char*** pointer to data loaded with csv_read().
 * @param data_dims size_t[2] array specifying dimensions of the data with the 0th index counting the rows and 1st index counting the columns
 * @param float_data An int** pointer passed by address to allocate and store the casted floats from data.
 */
void csv_data_to_float(char*** data, size_t data_dims[2], float*** float_data);

/**
 * @description Convert CSV column data (char**) to ints (int*)
 * @param data A char** pointer to data loaded with csv_read_column_by_name() or csv_read_column_by_index().
 * @param data_rows size_t variable specifying how many rows are present in the data.
 * @param int_data An int* pointer passed by address to allocate and store the casted integers from data.
 */
void csv_column_to_int(char** data, size_t data_rows, int** int_data);

/**
 * @description Convert CSV column data (char**) to ints (int*)
 * @param data A char** pointer to data loaded with csv_read_column_by_name() or csv_read_column_by_index().
 * @param data_rows size_t variable specifying how many rows are present in the data.
 * @param float_data A float* pointer passed by address to allocate and store the casted floats from data.
 */
void csv_column_to_float(char** data, size_t data_rows, float** float_data);

#endif //CSVPARSER_CAST_H
