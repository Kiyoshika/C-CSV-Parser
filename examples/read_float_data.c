#include "csvparser.h"

int main() {
    float** float_data = NULL;
    size_t data_dims[2];

    csv_read_float("./data/floats.csv", &float_data, &data_dims, ',', true);

    printf("\nFloat Data:\n");
    for (size_t i = 0; i < data_dims[0]; ++i)
    {
        for (size_t j = 0; j < data_dims[1]; ++j)
            printf("%f ", float_data[i][j]);
        printf("\n");
    }

    csv_free_float(&float_data, data_dims[0]);

    return 0;
}