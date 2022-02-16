#ifndef CSVPARSER_CSVPARSER_H
#define CSVPARSER_CSVPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t csv_parse_line(const char* line, char*** tokens, char delim);

#endif //CSVPARSER_CSVPARSER_H
