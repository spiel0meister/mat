#include <stdio.h>
#include <stdlib.h>

#define MAT_IMPLEMENTATION
#include "mat.h"

int main(void) {
    Mat* mat1 = mat_new(2, 3);

    for (size_t i = 0; i < mat1->rows; ++i) {
        for (size_t j = 0; j < mat1->columns; ++j) {
            mat_set(mat1, i, j, rand() % 10);
        }
    }

    mat_dump(mat1);
    Mat* mat2 = mat_scale(mat1, 10);
    mat_dump(mat2);

    mat_free(mat1);
    mat_free(mat2);

    return 0;
}
