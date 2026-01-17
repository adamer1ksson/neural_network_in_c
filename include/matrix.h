#pragma once
#include "base.h"
#include "arena.h"

typedef struct {
    // row major
    f32* data; 
    u64 rows;
    u64 cols;
} f_matrix;

typedef f32 (*f_func)(f32);

f_matrix f_matrix_create(mem_arena* arena, u64 rows, u64 cols);
void f_matrix_copy(f_matrix *out, f_matrix *a);
void f_matrix_add(f_matrix *out, f_matrix *a, f_matrix *b);
void f_matrix_sub(f_matrix *out, f_matrix *a, f_matrix *b);
void f_matrix_scale(f_matrix *a, f32 c);
void f_matrix_mult(f_matrix *out, f_matrix *a, f_matrix *b, bool a_transpose, bool b_transpose);
void f_matrix_transpose(f_matrix *a);
void f_matrix_transpose_copy(f_matrix *out, f_matrix *a);

void f_matrix_apply_func(f_func f, f_matrix* a);

void f_matrix_print(f_matrix* a);
