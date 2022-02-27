#ifndef CSVPARSER_SELECT_H
#define CSVPARSER_SELECT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @description Select columns from CSV file by name.
 * @param filename Filename to read CSV file from.
 * @param column_names An array of character strings specifying which columns to select from the CSV file.
 * @param n_columns Total number of columns being selected (length of column_names).
 * @param data char*** passed by address to store the CSV data.
 * @param data_dims A size_t[2] array passed by address with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim single-character delimiter.
 */
void csv_select_by_name(const char* filename, char** column_names, size_t n_columns, char**** data, size_t (*data_dims)[2], char delim);

/**
 * @description Select columns from CSV file by name and cast data to float.
 * @param filename Filename to read CSV file from.
 * @param column_names An array of character strings specifying which columns to select from the CSV file.
 * @param n_columns Total number of columns being selected (length of column_names).
 * @param data float** passed by address to store the CSV data.
 * @param data_dims A size_t[2] array passed by address with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim single-character delimiter.
 */
void csv_select_by_name_as_float(const char* filename, char** column_names, size_t n_columns, float*** data, size_t (*data_dims)[2], char delim);

/**
 * @description Select columns from CSV file by name and cast data to int.
 * @param filename Filename to read CSV file from.
 * @param column_names An array of character strings specifying which columns to select from the CSV file.
 * @param n_columns Total number of columns being selected (length of column_names).
 * @param data int** passed by address to store the CSV data.
 * @param data_dims A size_t[2] array passed by address with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim single-character delimiter.
 */
void csv_select_by_name_as_int(const char* filename, char** column_names, size_t n_columns, int*** data, size_t (*data_dims)[2], char delim);

/**
 * @description Select columns from CSV file by index.
 * @param filename Filename to read CSV file from.
 * @param column_indices A size_t array of indices specifying which columns to select from the CSV file.
 * @param n_columns Total number of columns being selected (length of column_indices).
 * @param data char*** passed by address to store the CSV data.
 * @param data_dims A size_t[2] array passed by address with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_select_by_index(const char* filename, size_t* column_indices, size_t n_columns, char**** data, size_t (*data_dims)[2], char delim, bool has_headers);

/**
 * @description Select columns from CSV file by index and cast data to float.
 * @param filename Filename to read CSV file from.
 * @param column_indices A size_t array of indices specifying which columns to select from the CSV file.
 * @param n_columns Total number of columns being selected (length of column_indices).
 * @param data float** passed by address to store the CSV data.
 * @param data_dims A size_t[2] array passed by address with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_select_by_index_as_float(const char* filename, size_t* column_indices, size_t n_columns, float*** data, size_t (*data_dims)[2], char delim, bool has_headers);

/**
 * @description Select columns from CSV file by index and cast data to int.
 * @param filename Filename to read CSV file from.
 * @param column_indices A size_t array of indices specifying which columns to select from the CSV file.
 * @param n_columns Total number of columns being selected (length of column_indices).
 * @param data int** passed by address to store the CSV data.
 * @param data_dims A size_t[2] array passed by address with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 */
void csv_select_by_index_as_int(const char* filename, size_t* column_indices, size_t n_columns, int*** data, size_t (*data_dims)[2], char delim, bool has_headers);

#endif //CSVPARSER_SELECT_H
