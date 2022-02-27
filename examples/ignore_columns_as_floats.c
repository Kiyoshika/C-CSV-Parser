#include "csvparser.h"

int main() {
    float** data = NULL;
    char* ignore_cols[2] = {"col1", "col3"};
    size_t data_dims[2];

    //csv_ignore_by_name("../examples/data/floats.csv", ignore_cols, 2, &data, &data_dims, ',');
    csv_ignore_by_name_as_float("./data/floats.csv", ignore_cols, 2, &data, &data_dims, ',');

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