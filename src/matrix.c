#include "stdio.h"

#include "../include/matrix.h"

f_matrix f_matrix_create(mem_arena* arena, u64 rows, u64 cols) {
    f_matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = PUSH_N_STRUCTS(arena, f32, rows*cols);
    return mat;
}

void f_matrix_copy(f_matrix *out, f_matrix *a) { 
    if (out->rows != a->rows || out->cols != a->cols) {
        fprintf(stderr, "Non matching dimensions for copy.\n");
        return;
    }
    u64 rows = a->rows;
    u64 cols = a->cols;
    for (u64 i = 0; i < rows; i++) {
        for (u64 j = i; j < cols; j++) {
            out->data[i*cols + j] = a->data[i*cols + j];
        }
    }
    return;
}

void f_matrix_add(f_matrix *out, f_matrix *a, f_matrix *b) {
    if (a->rows != b->rows || a->rows != out->rows || b->rows != out->rows ||
        a->cols != b->cols || a->cols != out->cols || b->cols != out->cols) {
        fprintf(stderr, "Adding matricies of different dimensions not allowed");        
        return;
    }
    u64 rows = out->rows;
    u64 cols = out->cols;
    for (u64 i = 0; i < rows; i++) {
        for (u64 j = 0; j < cols; j++) {
            u64 k = i*cols + j;
            out->data[k] = a->data[k] + b->data[k]; 
        }
    }
    return;
}
void f_matrix_sub(f_matrix *out, f_matrix *a, f_matrix *b) {
    if (a->rows != b->rows || a->rows != out->rows || b->rows != out->rows ||
        a->cols != b->cols || a->cols != out->cols || b->cols != out->cols) {
        fprintf(stderr, "Subtracting matricies of different dimensions not allowed");        
        return;
    }
    u64 rows = out->rows;
    u64 cols = out->cols;
    for (u64 i = 0; i < rows; i++) {
        for (u64 j = 0; j < cols; j++) {
            u64 k = i*cols + j;
            out->data[k] = a->data[k] - b->data[k]; 
        }
    }
    return;
}
void f_matrix_scale(f_matrix *out, f32 c) {
    u64 rows = out->rows;
    u64 cols = out->cols;
    for (u64 i = 0; i < rows; i++) {
        for (u64 j = 0; j < cols; j++) {
            out->data[i*cols + j] *= c;
        }
    }
    return;
}

void f_matrix_mult(f_matrix *out, f_matrix *a, f_matrix *b, bool a_transpose, bool b_transpose) {
    if (a_transpose && b_transpose) {
        if (a->rows != b->cols || a->cols != out->rows || b->rows != out->cols) { 
            fprintf(stderr, "Non matching dimensions of matricies in multiplication");
            return;
        }
        u64 orows = a->cols;
        u64 ocols = b->rows;
        u64 inner = a->rows;
        for (u64 i=0; i < orows; i++) {
            for (u64 j=0; j < ocols; j++) {
                for (u64 k=0; k < inner; k++) {
                    out->data[i*ocols+ j] +=
                        a->data[k*inner + i] *
                        b->data[j*ocols + k];
                }
            }    
        }
        return;
    } else if (a_transpose && !b_transpose) {
        if (a->rows != b->rows || a->cols != out->rows || b->cols != out->cols) { 
            fprintf(stderr, "Non matching dimensions of matricies in multiplication");
            return;
        }
        u64 orows = a->cols;
        u64 ocols = b->cols;
        u64 inner = a->rows;
        for (u64 k=0; k < inner; k++) {
            for (u64 i=0; i < orows; i++) {
                for (u64 j=0; j < ocols; j++) {
                    out->data[i*ocols + j] +=
                        a->data[k*inner + i] *
                        b->data[k*ocols + j];
                }
            }    
        }    
        return;
    } else if (!a_transpose && b_transpose) {
        if (a->cols != b->cols || a->rows != out->rows || b->rows != out->cols) { 
            fprintf(stderr, "Non matching dimensions of matricies in multiplication");
            return;
        }
        u64 orows = a->rows;
        u64 ocols = b->rows;
        u64 inner = a->cols;
        for (u64 i=0; i < orows; i++) {
            for (u64 j=0; j < ocols; j++) {
                for (u64 k=0; k < inner; k++) {
                    out->data[i*ocols + j] +=
                        a->data[i*inner + k] *
                        b->data[j*ocols + k];
                }
            }    
        }    
        return;
    }
    if (a->cols != b->rows || a->rows != out->rows || b->cols != out->cols) { 
        fprintf(stderr, "Non matching dimensions of matricies in multiplication");
        return;
    }
    u64 orows = a->rows;
    u64 ocols = b->cols;
    u64 inner = a->cols;
    for (u64 i=0; i < orows; i++) {
        for (u64 k=0; k < inner; k++) {
            for (u64 j=0; j < ocols; j++) {
                out->data[i*ocols + j] +=
                    a->data[i*inner + k] *
                    b->data[k*ocols + j];
            }
        }    
    }    
    return;
}

void f_matrix_transpose(f_matrix *a) {
    u64 rows = a->rows;
    u64 cols = a->cols;
    for (u64 i = 0; i < rows; i++) {
        for (u64 j = i; j < cols; j++) {
            f32 temp = a->data[i*cols + j];
            a->data[i*cols + j] = a->data[j*cols + i];
            a->data[j*cols + i] = temp;
        }
    }
    a->rows = cols;
    a->cols = rows;
    return;
}

void f_matrix_transpose_copy(f_matrix *out, f_matrix *a) {
    if (out->rows != a->cols || out->cols != a->rows) {
        fprintf(stderr, "Non matching dimensions for transpose copy.\n");
        return;
    }
    u64 rows = a->rows;
    u64 cols = a->cols;
    for (u64 i = 0; i < rows; i++) {
        for (u64 j = i; j < cols; j++) {
            out->data[j*rows + i] = a->data[i*cols + j];
        }
    }
    return;
}

void f_matrix_apply_func(f_func function, f_matrix* a) {
    u64 rows = a->rows;
    u64 cols = a->cols;
    for (u64 i = 0; i < rows; i++) {
        for (u64 j = i; j < cols; j++) {
            a->data[i*cols + j] = function(a->data[i*cols + j]);
        }
    }
}

void f_matrix_print(f_matrix* a) {
    printf("\n");
    u64 rows = a->rows;
    u64 cols = a->cols;
    for (u64 i = 0; i < rows; i++) {
        for (u64 j = 0; j < cols; j++) {
            printf(" %.2f ", a->data[i*cols + j]); 
        }
        printf("\n");
    }
    printf("\n");
    return;
}



