#ifndef CSVPARSER_CSVPARSER_H
#define CSVPARSER_CSVPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Read a CSV file and store cells into a char*** pointer.
 * @param filename Filename to read CSV file from.
 * @param data A char*** that holds the CSV cells (need to pass by address, hence the parameter is char****). It's structured as data[x][y] where x represents the row, y represents the column and the contents is a string (char*).
 * @param data_dims A size_t array with two indices: 0th index stores the row count and 1st index stores the column count.
 * @param delim A single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 *
 * Example:
 * @code
 * #include "csvparser.h"
 *
 * int main() {
 *     char*** data = NULL;
 *     size_t data_dims[2];
 *
 *     csv_read("../test.csv", &data, &data_dims, ',', true);
 *
 *     printf("Rows: %zu\nColumns: %zu\n\n", data_dims[0], data_dims[1]);
 *
 *     // print all cells of the parsed data
 *     for (size_t i = 0; i < data_dims[0]; ++i)
 *     {
 *         for (size_t j = 0; j < data_dims[1]; ++j)
 *         {
 *             printf("%s ", data[i][j]);
 *         }
 *         printf("\n");
 *     }
 *
 *     // don't forget to free all the memory allocated to store the strings
 *     csv_free(&data, data_dims);
 *
 *     return 0;
 * }
 * @endcode
 *
 * Output:
 *
 * @code
 * Rows: 3
 * Columns: 3
 *
 * 10 joe 10.33
 * 20 jim 41.55
 * 30 kyle -3.55
 * @endcode
 */
void csv_read(const char* filename, char**** data, size_t (*data_dims)[2], char delim, bool has_headers);

/**
 * Read a single column (by index) from CSV file and store cells into a char** pointer.
 * @param filename Filename to read CSV file from.
 * @param column_index Index of the column to read.
 * @param data A char** that holds the CSV cells from the specified column
 * @param delim A single-character delimiter.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 *
 */
void csv_read_column_by_index(const char* filename, size_t column_index, char*** data, char delim, bool has_headers);

/**
 * Read a single column (by name) from CSV file and store cells into a char** pointer.
 * @param filename Filename to read CSV file from.
 * @param column_index Index of the column to read.
 * @param data A char** that holds the CSV cells from the specified column
 * @param delim A single-character delimiter.
 *
 */
void csv_read_column_by_name(const char* filename, size_t column_index, char*** data, char delim);

/**
 * Free the memory allocated to data after reading a CSV file. This MUST be done if you intent on using the same pointer to read a different file.
 * @param data The address to a char*** pointer holding the CSV data loaded by csv_read().
 * @param data_dims Array of data dimensions with the 0th index counting the rows and 1st index counting the columns.
 */
void csv_free(char**** data, size_t data_dims[2]);

// inactive for now
void csv_free_column(char*** data, size_t rows);

#endif //CSVPARSER_CSVPARSER_H
