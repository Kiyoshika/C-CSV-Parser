#include "csvparser.h"

int main() {
    float** data = NULL;
    size_t data_dims[2];
    char* columns[2] = {"col1", "col2"};

    csv_select_by_name_as_float("../examples/data/floats.csv", columns, 2, &data, &data_dims, ',');

    printf("Data:\n");
    for (size_t r = 0; r < data_dims[0]; ++r)
    {
        for (size_t c = 0; c < data_dims[1]; ++c)
            printf("%f ", data[r][c]);
        printf("\n");
    }

    csv_free_float(&data, data_dims[0]);

    return 0;
}