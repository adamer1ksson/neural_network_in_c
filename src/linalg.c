#include "stdio.h"

#include "../include/linalg.h"
#include "../include/base.h"
#include "../include/vector.h"
#include "../include/matrix.h"

void f_matrix_scale_row(f_matrix* a, f32 c, u64 index) {
    if (index >= a->rows) {
        fprintf(stderr, "Row index out of range.\n");
        return;
    }
    for (u64 j = 0; j < a->cols; j++) {
        a->data[index*a->cols + j] *= c;
        f_matrix_print(a);
    }
    return;
}
void f_matrix_add_row_to_row(f_matrix* a, u64 row, u64 to_row) {
    if (row >= a->rows || to_row >= a->rows) {
        fprintf(stderr, "Row index out of range.\n");
        return;
    }
    for (u64 j = 0; j < a->cols; j++) {
        a->data[to_row*a->cols + j] += a->data[row*a->cols + j];
    }
    return;
}

void f_matrix_ref(f_matrix* a) {
    u64 rows = a->rows;
    u64 cols = a->cols;
    for (u64 i = 0; i < rows-1; i++) {
        f32 lead = a->data[i*cols + i];
        f_matrix_scale_row(a, -1/lead, i);
        for (u64 j = i+1; j < rows; j++) {
            f_matrix_add_row_to_row(a, i, j); 
        }
        f_matrix_scale_row(a, -1, i);
    }
    return;
}

void f_matrix_vect_mult(f_vect* out, f_matrix* a, f_vect* b) {
    if (a->cols != b->len || out->len != a->rows) {
        fprintf(stderr, "Non matching dimensions in matrix vector multiplication.\n");
        return;
    }
    u64 rows = a->rows;
    u64 cols = a->cols;
    for (u64 i = 0; i < rows; i++) {
        for (u64 j = 0; j < cols; j++) {
            out->data[i] += a->data[i*cols + j] * b->data[j];
        }
    }
    return;
}

