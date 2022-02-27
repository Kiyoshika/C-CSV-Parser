#ifndef CSVPARSER_CSVPARSER_H
#define CSVPARSER_CSVPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @description Read a CSV file and store cells into a char*** pointer.
 * @param filename Filename to read CSV file from.
 * @param data A char*** passed by address that holds the CSV cells. It's structured as data[x][y] where x represents the row, y represents the column and the contents is a string (char*).
 * @param data_dims A size_t[2] array passed by address with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim A single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_read(const char* filename, char**** data, size_t (*data_dims)[2], char delim, bool has_headers);

/**
 * @description Read a CSV file and cast data to int.
 * @param filename Filename to read CSV file from.
 * @param data An int** passed by address that holds the CSV cells. It's structured as data[x][y] where x represents the row, y represents the column
 * @param data_dims A size_t[2] array passed by address with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim A single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_read_int(const char* filename, int*** data, size_t (*data_dims)[2], char delim, bool has_headers);

/**
 * @description Read a CSV file and cast data to float.
 * @param filename Filename to read CSV file from.
 * @param data A float** passed by address that holds the CSV cells. It's structured as data[x][y] where x represents the row, y represents the column
 * @param data_dims A size_t[2] array passed by address with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim A single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_read_float(const char* filename, float*** data, size_t (*data_dims)[2], char delim, bool has_headers);

/**
 * @description Read a single column (by index) from CSV file and store cells into a char** pointer.
 * @param filename Filename to read CSV file from.
 * @param column_index Index of the column to read.
 * @param data A char** passed by address that holds the CSV cells from the specified column
 * @param delim A single-character delimiter.
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 *
 */
void csv_read_column_by_index(const char* filename, size_t column_index, char*** data, char delim, size_t* data_rows, bool has_headers);

/**
 * @description Read a single column (by index) from CSV file and cast data to float.
 * @param filename Filename to read CSV file from.
 * @param column_index Index of the column to read.
 * @param data A float* passed by address that holds the CSV cells from the specified column
 * @param delim A single-character delimiter.
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_read_column_by_index_as_float(const char* filename, size_t column_index, float** data, char delim, size_t* data_rows, bool has_headers);

/**
 * @description Read a single column (by index) from CSV file and cast data to int.
 * @param filename Filename to read CSV file from.
 * @param column_index Index of the column to read.
 * @param data An int* passed by address that holds the CSV cells from the specified column
 * @param delim A single-character delimiter.
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_read_column_by_index_as_int(const char* filename, size_t column_index, int** data, char delim, size_t* data_rows, bool has_headers);

/**
 * @description Read a single column (by name) from CSV file and store cells into a char** pointer.
 * @param filename Filename to read CSV file from.
 * @param column_name Name of the column to read.
 * @param data A char** passed by address that holds the CSV cells from the specified column.
 * @param delim A single-character delimiter.
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 */
void csv_read_column_by_name(const char* filename, const char* column_name, char*** data, char delim, size_t* data_rows);

/**
 * @description Read a single column (by name) from CSV file and cast data to float.
 * @param filename Filename to read CSV file from.
 * @param column_name Name of the column to read.
 * @param data A float* passed by address that holds the CSV cells from the specified column.
 * @param delim A single-character delimiter.
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 */
void csv_read_column_by_name_as_float(const char* filename, const char* column_name, float** data, char delim, size_t* data_rows);

/**
 * @description Read a single column (by name) from CSV file and cast data to int.
 * @param filename Filename to read CSV file from.
 * @param column_name Name of the column to read.
 * @param data An int* passed by address that holds the CSV cells from the specified column.
 * @param delim A single-character delimiter.
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 */
void csv_read_column_by_name_as_int(const char* filename, const char* column_name, int** data, char delim, size_t* data_rows);

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

#endif //CSVPARSER_CSVPARSER_H
