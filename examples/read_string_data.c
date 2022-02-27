#include "csvparser.h"

int main() {
    char*** data = NULL;
    size_t data_dims[2];

    // CSV reader supports delimiters inside quotes
    csv_read("./data/text.csv", &data, &data_dims, ',', true);

    printf("\nString Data:\n");
    for (size_t i = 0; i < data_dims[0]; ++i)
    {
        for (size_t j = 0; j < data_dims[1]; ++j)
            printf("%s ", data[i][j]);
        printf("\n");
    }

    csv_free(&data, data_dims);

    return 0;
}