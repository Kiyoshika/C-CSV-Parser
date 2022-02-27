#include "csvparser.h"

int main() {
    float* data = NULL;
    size_t rows;

    csv_read_column_by_index_as_float("./data/floats.csv", 0, &data, ',', &rows, true);

    printf("Float Data:\n");
    for (size_t i = 0; i < rows; ++i)
        printf("%f\n", data[i]);

    csv_free_column_float(&data);

    return 0;
}