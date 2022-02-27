#include "csvparser.h"

int main() {
    char*** data = NULL;
    float** float_data = NULL;
    size_t data_dims[2];

    csv_read("./data/floats.csv", &data, &data_dims, ',', true);

    csv_data_to_float(data, data_dims, &float_data);

    printf("\nString Data:\n");
    for (size_t i = 0; i < data_dims[0]; ++i)
    {
        for (size_t j = 0; j < data_dims[1]; ++j)
            printf("%s ", data[i][j]);
        printf("\n");
    }

    printf("\nFloat Data:\n");
    for (size_t i = 0; i < data_dims[0]; ++i)
    {
        for (size_t j = 0; j < data_dims[1]; ++j)
            printf("%f ", float_data[i][j]);
        printf("\n");
    }

    csv_free(&data, data_dims);
    csv_free_float(&float_data, data_dims[0]);

    return 0;
}