#ifndef CSVPARSER_FREE_H
#define CSVPARSER_FREE_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @description Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a char*** pointer holding the CSV data loaded by csv_read().
 * @param data_dims Array of data dimensions with the 0th index counting the rows and 1st index counting the columns.
 */
void csv_free(char**** data, size_t data_dims[2]);

/**
 * @description Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to an int** pointer holding the CSV data loaded by csv_data_to_int().
 * @param data_rows How many rows to free from the data.
 *
 */
void csv_free_int(int*** data, size_t data_rows);

/**
 * @description Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a float** pointer holding the CSV data loaded by csv_data_to_float().
 * @param data_rows How many rows to free from the data.
 *
 */
void csv_free_float(float*** data, size_t data_rows);

/**
 * @description Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a char** pointer holding the CSV data loaded by csv_read_column().
 * @param data_rows How many rows to free from the data.
 */
void csv_free_column(char*** data, size_t data_rows);

/**
 * @description Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a int* pointer holding the CSV data loaded by csv_read_column_int().
 * @param data_rows How many rows to free from the data.
 */
void csv_free_column_int(int** data);

/**
 * @description Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a float* pointer holding the CSV data loaded by csv_read_column_float().
 * @param data_rows How many rows to free from the data.
 */
void csv_free_column_float(float** data);

#endif //CSVPARSER_FREE_H
