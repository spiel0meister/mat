#ifndef MAT_H
#define MAT_H
#include <stdio.h>
#include <stddef.h>

typedef struct {
    size_t rows, columns;
    double nums[];
}Mat;

Mat* mat_new(size_t rows, size_t columns);
Mat* mat_zeroes(size_t rows, size_t columns);
Mat* mat_new_identity(size_t side);
#define mat_free free

double mat_get(Mat* self, size_t row, size_t column);
void mat_set(Mat* self, size_t row, size_t column, double value);

void mat_fdump(Mat* self, FILE* sink);
#define mat_dump(self) mat_fdump(self, stdout)

Mat* mat_add(Mat* a, Mat* b);
Mat* mat_sub(Mat* a, Mat* b);

Mat* mat_scale(Mat* a, double scalar);
Mat* mat_mult(Mat* a, Mat* b);

#endif // MAT_H

#ifdef MAT_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Mat* mat_new_identity(size_t side) {
    Mat* out = mat_zeroes(side, side);

    for (size_t i = 0; i < side; ++i) {
        mat_set(out, i, i, 1.0);
    }

    return out;
}

Mat* mat_new(size_t rows, size_t columns) {
    assert(rows > 0);
    assert(columns > 0);

    Mat* mat = malloc(sizeof(mat->rows) + sizeof(mat->columns) + sizeof(*mat->nums) * rows * columns);
    assert(mat != NULL && "Buy more RAM lol");
    mat->rows = rows;
    mat->columns = columns;
    return mat;
}

Mat* mat_zeroes(size_t rows, size_t columns) {
    assert(rows > 0);
    assert(columns > 0);

    Mat* mat = malloc(sizeof(mat->rows) + sizeof(mat->columns) + sizeof(*mat->nums) * rows * columns);
    assert(mat != NULL && "Buy more RAM lol");
    mat->rows = rows;
    mat->columns = columns;
    memset(mat->nums, 0, sizeof(*mat->nums) * rows * columns);
    return mat;
}

double mat_get(Mat* self, size_t row, size_t column) {
    assert(row < self->rows);
    assert(column < self->columns);
    return self->nums[row * self->columns + column];
}

void mat_set(Mat* self, size_t row, size_t column, double value) {
    assert(row < self->rows);
    assert(column < self->columns);
    self->nums[row * self->columns + column] = value;
}

Mat* mat_add(Mat* a, Mat* b) {
    assert(a->rows == b->rows);
    assert(a->columns == b->columns);

    Mat* out = mat_new(a->rows, a->columns);
    for (size_t row = 0; row < a->rows; ++row) {
        for (size_t column = 0; column < a->columns; ++column) {
            mat_set(out, row, column, mat_get(a, row, column) + mat_get(b, row, column));
        }
    }

    return out;
}

Mat* mat_sub(Mat* a, Mat* b) {
    assert(a->rows == b->rows);
    assert(a->columns == b->columns);

    Mat* out = mat_new(a->rows, a->columns);
    for (size_t row = 0; row < a->rows; ++row) {
        for (size_t column = 0; column < a->columns; ++column) {
            mat_set(out, row, column, mat_get(a, row, column) - mat_get(b, row, column));
        }
    }

    return out;
}

Mat* mat_scale(Mat* a, double scalar) {
    Mat* out = mat_new(a->rows, a->columns);

    for (size_t row = 0; row < a->rows; ++row) {
        for (size_t column = 0; column < a->columns; ++column) {
            mat_set(out, row, column, mat_get(a, row, column) * scalar);
        }
    }

    return out;
}

Mat* mat_mult(Mat* a, Mat* b) {
    assert(a->columns == b->rows);
    assert(a->rows == b->columns);

    /*
     * [1, 2, 3]
     * [4, 5, 6]
     *
     * [7,   8]
     * [9,  10]
     * [11, 12]
     * */

    Mat* out = mat_new(a->rows, b->columns);

    for (size_t out_row = 0; out_row < out->rows; ++out_row) {
        for (size_t out_column = 0; out_column < out->columns; ++out_column) {
            double dot_product = 0.0;
            for (size_t i = 0; i < a->columns; ++i) {
                dot_product += mat_get(a, out_row, i) * mat_get(b, i, out_column);
            }
            mat_set(out, out_row, out_column, dot_product);
        }
    }

    return out;
}

void mat_fdump(Mat* self, FILE* sink) {
    for (size_t row = 0; row < self->rows; ++row) {
        for (size_t column = 0; column < self->columns; ++column) {
            fprintf(sink, "%lf ", mat_get(self, row, column));
        }
        fprintf(sink, "\n");
    }
}

#endif // MAT_IMPLEMENTATION
