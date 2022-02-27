#include "csvparser.h"

int main() {
    char*** data = NULL;
    char* ignore_cols[2] = {"col1", "col3"};
    size_t data_dims[2];
    size_t indices[2] = {0, 2};

    // this will only read col2 as we are ignoring col1 and col3
    csv_ignore_by_name("./data/floats.csv", ignore_cols, 2, &data, &data_dims, ',');

    printf("Data:\n");
    for (size_t r = 0; r < data_dims[0]; ++r)
    {
        for (size_t c = 0; c < data_dims[1]; ++c)
            printf("%s ", data[r][c]);
        printf("\n");
    }

    csv_free(&data, data_dims);

    return 0;
}