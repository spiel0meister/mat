#include <stdio.h>
#include <stdlib.h>

#define MAT_IMPLEMENTATION
#include "mat.h"

int main(void) {
    Mat* mat1 = mat_new(2, 3);

    mat_it_rows(mat1, i) {
        mat_it_columns(mat1, j) {
            mat_set(mat1, i, j, rand() % 10);
        }
    }

    mat_dump(mat1);
    printf("---\n");
    Mat* mat2 = mat_scale(mat1, 10);
    mat_dump(mat2);

    mat_free(mat1);
    mat_free(mat2);

    return 0;
}
