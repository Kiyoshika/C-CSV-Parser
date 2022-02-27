#ifndef CSVPARSER_CSVINTERNAL_H
#define CSVPARSER_CSVINTERNAL_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// internal function
// counts columns based on delimiter
// used to size the tokens array within csv_parse_line
size_t csv_count_columns(const char* line, char delim);

// internal function
// parses a line of CSV and stores parsed values into tokens
// tokens must be freed by the client
// returns number of tokens that were extracted. can be used by client when freeing memory
size_t csv_parse_line(const char* line, char delim, char*** tokens);

// internal function
// get the column names and return how many columns are present.
// this is a special case of csv_parse_line() where we pass the filename and read the first line
// rather than specifying the actual line within the file
size_t csv_get_column_names(const char* filename, char delim, char*** columns);

#endif //CSVPARSER_CSVINTERNAL_H
