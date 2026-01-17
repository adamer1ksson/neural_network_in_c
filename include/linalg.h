#pragma once
#include "base.h"
#include "vector.h"
#include "matrix.h"

void f_matrix_scale_row(f_matrix* a, f32 c, u64 index);
void f_matrix_add_row_to_row(f_matrix* a, u64 row, u64 to_row);
void f_matrix_ref(f_matrix* a);

void f_matrix_vect_mult(f_vect* out, f_matrix* a, f_vect* b);

