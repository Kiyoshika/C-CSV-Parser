#ifndef CSVPARSER_READ_H
#define CSVPARSER_READ_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 * @param delim A single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 *
 */
void csv_read_column_by_index(const char* filename, size_t column_index, char*** data, size_t* data_rows, char delim, bool has_headers);

/**
 * @description Read a single column (by index) from CSV file and cast data to float.
 * @param filename Filename to read CSV file from.
 * @param column_index Index of the column to read.
 * @param data A float* passed by address that holds the CSV cells from the specified column
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 * @param delim A single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_read_column_by_index_as_float(const char* filename, size_t column_index, float** data, size_t* data_rows, char delim, bool has_headers);

/**
 * @description Read a single column (by index) from CSV file and cast data to int.
 * @param filename Filename to read CSV file from.
 * @param column_index Index of the column to read.
 * @param data An int* passed by address that holds the CSV cells from the specified column
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 * @param delim A single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_read_column_by_index_as_int(const char* filename, size_t column_index, int** data, size_t* data_rows, char delim, bool has_headers);

/**
 * @description Read a single column (by name) from CSV file and store cells into a char** pointer.
 * @param filename Filename to read CSV file from.
 * @param column_name Name of the column to read.
 * @param data A char** passed by address that holds the CSV cells from the specified column.
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 * @param delim A single-character delimiter.
 */
void csv_read_column_by_name(const char* filename, const char* column_name, char*** data, size_t* data_rows, char delim);

/**
 * @description Read a single column (by name) from CSV file and cast data to float.
 * @param filename Filename to read CSV file from.
 * @param column_name Name of the column to read.
 * @param data A float* passed by address that holds the CSV cells from the specified column.
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 * @param delim A single-character delimiter.
 */
void csv_read_column_by_name_as_float(const char* filename, const char* column_name, float** data, size_t* data_rows, char delim);

/**
 * @description Read a single column (by name) from CSV file and cast data to int.
 * @param filename Filename to read CSV file from.
 * @param column_name Name of the column to read.
 * @param data An int* passed by address that holds the CSV cells from the specified column.
 * @param data_rows A size_t variable passed by address to store the number of rows after parsing CSV file.
 * @param delim A single-character delimiter.
 */
void csv_read_column_by_name_as_int(const char* filename, const char* column_name, int** data, size_t* data_rows, char delim);

#endif //CSVPARSER_READ_H
