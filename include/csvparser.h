#ifndef CSVPARSER_CSVPARSER_H
#define CSVPARSER_CSVPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Read a CSV file and store cells into a char*** pointer.
 * @param filename Filename to read CSV file from.
 * @param data A char**** pointer (char*** passed by address) that holds the CSV cells (need to pass by address, hence the parameter is char****). It's structured as data[x][y] where x represents the row, y represents the column and the contents is a string (char*).
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
void csv_read(const char* filename, char**** data, char delim, size_t (*data_dims)[2], bool has_headers);

/**
 * Read a single column (by index) from CSV file and store cells into a char** pointer.
 * @param filename Filename to read CSV file from.
 * @param column_index Index of the column to read.
 * @param data A char*** pointer (char** passed by address) that holds the CSV cells from the specified column
 * @param delim A single-character delimiter.
 * @param data_rows A size_t* pointer (passed by address) to store the number of rows after parsing CSV file.
 * @param has_headers A boolean indicating if the file has headers or not. If true, the first line will be skipped and not stored into data.
 *
 * Example:
 *
 * @code
 * #include "csvparser.h"
 *
 * int main() {
 *     char** data = NULL;
 *     size_t rows;
 *     csv_read_column_by_index("../test.csv", 1, &data, ',', &rows, true);
 *
 *     printf("Rows: %zu\n", rows);
 *
 *     // print all cells of the parsed data
 *     for (size_t i = 0; i < rows; ++i)
 *         printf("%s\n", data[i]);
 *
 *     // don't forget to free all the memory allocated to store the strings
 *     csv_free_column(&data, rows);
 *
 *     return 0;
 * }
 * @endcode
 *
 * Output: (this is the second column (1st index) of my sample CSV file)
 *
 * @code
 * Rows: 3
 * joe
 * jim
 * kyle
 * @endcode
 *
 */
void csv_read_column_by_index(const char* filename, size_t column_index, char*** data, char delim, size_t* data_rows, bool has_headers);

/**
 * Read a single column (by name) from CSV file and store cells into a char** pointer.
 * @param filename Filename to read CSV file from.
 * @param column_name Name of the column to read.
 * @param data A char*** pointer (char** passed by address) that holds the CSV cells from the specified column.
 * @param delim A single-character delimiter.
 * @param data_rows A size_t* pointer (passed by address) to store the number of rows after parsing CSV file.
 *
 * Example:
 *
 * @code
 * #include "csvparser.h"
 *
 * int main() {
 *     char** data = NULL;
 *     size_t rows;
 *     csv_read_column_by_name("../test.csv", "col2", &data, ',', &rows);
 *
 *     printf("Rows: %zu\n", rows);
 *
 *     // print all cells of the parsed data
 *     for (size_t i = 0; i < rows; ++i)
 *         printf("%s\n", data[i]);
 *
 *     // don't forget to free all the memory allocated to store the strings
 *     csv_free_column(&data, rows);
 *
 *     return 0;
 * }
 *
 * @endcode
 *
 * Output:
 *
 * @code
 * Rows: 3
 * joe
 * jim
 * kyle
 * @endcode
 */
void csv_read_column_by_name(const char* filename, const char* column_name, char*** data, char delim, size_t* data_rows);

/**
 * Convert CSV data (char***) to integers (int**).
 * @param data A char*** pointer to data loaded with csv_read().
 * @param data_dims Array specifying dimensions of the data with the 0th index counting the rows and 1st index counting the columns
 * @param int_data An int** pointer passed by address to allocate and store the casted integers from data.
 * Example:
 *
 * @code
 * #include "csvparser.h"
 *
 * int main() {
 *     char*** data = NULL;
 *     int** int_data = NULL;
 *     size_t data_dims[2];
 *
 *     csv_read("../test.csv", &data, ',', &data_dims, true);
 *
 *     csv_data_to_int(data, &data_dims, &int_data);
 *
 *     printf("String Data:\n");
 *     for (size_t i = 0; i < data_dims[0]; ++i)
 *     {
 *         for (size_t j = 0; j < data_dims[1]; ++j)
 *         {
 *             printf("%s ", data[i][j]);
 *         }
 *         printf("\n");
 *     }
 *
 *     printf("\nInt Data:\n");
 *     for (size_t i = 0; i < data_dims[0]; ++i)
 *     {
 *         for (size_t j = 0; j < data_dims[1]; ++j)
 *         {
 *             printf("%d ", int_data[i][j]);
 *         }
 *         printf("\n");
 *     }
 *
 *     // don't forget to free all the memory allocated to store the strings
 *     csv_free(&data, data_dims);
 *     csv_free_int(&int_data, data_dims[0]);
 *
 *     return 0;
 * }
 *
 * @endcode
 *
 * Output:
 *
 * @code
 * String Data:
 * 10 "bob,joe,kyle" 10.33
 * 20 jim 8.11
 * 30 kyle "13.52,20.111"
 *
 * Int Data:
 * 10 0 10
 * 20 0 8
 * 30 0 0
 * @endcode
 */
void csv_data_to_int(char*** data, size_t (*data_dims)[2], int*** int_data);

/**
 *
 * @param data A char*** pointer to data loaded with csv_read().
 * @param data_dims Array specifying dimensions of the data with the 0th index counting the rows and 1st index counting the columns
 * @param float_data A float** pointer passed by address to allocate and store the casted floats from data.
 *
 * Example:
 *
 * @code
 * #include "csvparser.h"
 *
 * int main() {
 *     char*** data = NULL;
 *     float** float_data = NULL;
 *     size_t data_dims[2];
 *
 *     csv_read("../test.csv", &data, ',', &data_dims, true);
 *
 *     csv_data_to_float(data, &data_dims, &float_data);
 *
 *     printf("String Data:\n");
 *     for (size_t i = 0; i < data_dims[0]; ++i)
 *     {
 *          for (size_t j = 0; j < data_dims[1]; ++j)
 *             printf("%s ", data[i][j]);
 *         printf("\n");
 *     }
 *
 *     printf("\nFloat Data:\n");
 *     for (size_t i = 0; i < data_dims[0]; ++i)
 *     {
 *         for (size_t j = 0; j < data_dims[1]; ++j)
 *             printf("%f ", float_data[i][j]);
 *         printf("\n");
 *     }
 *
 *     // don't forget to free all the memory allocated to store the strings
 *     csv_free(&data, data_dims);
 *     csv_free_float(&float_data, data_dims[0]);
 *
 *     return 0;
 * }
 * @endcode
 *
 * Output:
 *
 * @code
 * String Data:
 * 10 "bob,joe,kyle" 10.33
 * 20 jim 8.11
 * 30 kyle "13.52,20.111"
 *
 * Float Data:
 * 10.000000 0.000000 10.330000
 * 20.000000 0.000000 8.110000
 * 30.000000 0.000000 0.000000
 * @endcode
 */
void csv_data_to_float(char*** data, size_t (*data_dims)[2], float*** float_data);

/**
 *
 * @param data A char** pointer to data loaded with csv_read_column_by_name() or csv_read_column_by_index().
 * @param data_rows How many rows are present in the data.
 * @param int_data An int* pointer passed by address to allocate and store the casted integers from data.
 *
 * Example:
 *
 * @code
 * #include "csvparser.h"
 *
 * int main() {
 *     char** data = NULL;
 *     int* int_data = NULL;
 *     size_t data_rows;
 *     csv_read_column_by_index("../test.csv", 0, &data, ',', &data_rows, true);
 *
 *     csv_column_to_int(data, data_rows, &int_data);
 *
 *     printf("String Data:\n");
 *     for (size_t i = 0; i < data_rows; ++i)
 *         printf("%s\n", data[i]);
 *
 *     printf("\nInt Data:\n");
 *     for (size_t i = 0; i < data_rows; ++i)
 *         printf("%d\n", int_data[i] + 1);
 *
 *     // don't forget to free all the memory allocated to store the strings
 *     csv_free_column(&data, data_rows);
 *     csv_free_column_int(&int_data);
 *
 *     return 0;
 * }
 * @endcode
 *
 * Output:
 *
 * @code
 * String Data:
 * 10
 * 20
 * 30
 *
 * Int Data:
 * 11
 * 21
 * 31
 * @endcode
 */
void csv_column_to_int(char** data, size_t data_rows, int** int_data);

/**
 *
 * @param data A char** pointer to data loaded with csv_read_column_by_name() or csv_read_column_by_index().
 * @param data_rows How many rows are present in the data.
 * @param float_data A float* pointer passed by address to allocate and store the casted floats from data.
 *
 * Example:
 *
 * @code
 * #include "csvparser.h"
 *
 * int main() {
 *     char** data = NULL;
 *     float* float_data = NULL;
 *     size_t data_rows;
 *     csv_read_column_by_index("../test.csv", 0, &data, ',', &data_rows, true);
 *
 *     csv_column_to_float(data, data_rows, &float_data);
 *
 *     printf("String Data:\n");
 *     for (size_t i = 0; i < data_rows; ++i)
 *         printf("%s\n", data[i]);
 *
 *     printf("\nFloat Data:\n");
 *     for (size_t i = 0; i < data_rows; ++i)
 *         printf("%f\n", float_data[i] + 1.0);
 *
 *     // don't forget to free all the memory allocated to store the strings
 *     csv_free_column(&data, data_rows);
 *     csv_free_column_float(&float_data);
 *
 *     return 0;
 * }
 * @endcode
 *
 * Output:
 *
 * @code
 * String Data:
 * 10
 * 20
 * 30
 *
 * Float Data:
 * 11.000000
 * 21.000000
 * 31.000000
 * @endcode
 */
void csv_column_to_float(char** data, size_t data_rows, float** float_data);

/**
 * Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a char*** pointer holding the CSV data loaded by csv_read().
 * @param data_dims Array of data dimensions with the 0th index counting the rows and 1st index counting the columns.
 */
void csv_free(char**** data, size_t data_dims[2]);

/**
 * Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to an int** pointer holding the CSV data loaded by csv_data_to_int().
 * @param data_rows How many rows to free from the data.
 *
 */
void csv_free_int(int*** data, size_t data_rows);

/**
 * Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a float** pointer holding the CSV data loaded by csv_data_to_float().
 * @param data_rows How many rows to free from the data.
 *
 */
void csv_free_float(float*** data, size_t data_rows);

/**
 * Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a char** pointer holding the CSV data loaded by csv_read_column().
 * @param data_rows How many rows to free from the data.
 */
void csv_free_column(char*** data, size_t data_rows);

/**
 * Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a int* pointer holding the CSV data loaded by csv_read_column_int().
 * @param data_rows How many rows to free from the data.
 */
void csv_free_column_int(int** data);

/**
 * Free the memory allocated to data after reading a CSV file. This MUST be done if you intend on using the same pointer to read a different file.
 * @param data The address to a float* pointer holding the CSV data loaded by csv_read_column_float().
 * @param data_rows How many rows to free from the data.
 */
void csv_free_column_float(float** data);

#endif //CSVPARSER_CSVPARSER_H
