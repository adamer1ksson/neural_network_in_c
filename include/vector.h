#pragma once
#include "base.h"
#include "arena.h"

typedef struct {
    f32* data;
    u64 len;
} f_vect;

f_vect f_vect_create(mem_arena* arena, u64 len);

void f_vect_add(f_vect *out, f_vect *a, f_vect *b);
void f_vect_sub(f_vect *out, f_vect *a, f_vect *b);
f32 f_vect_dot(f_vect *a, f_vect *b);
f32 f_vect_norm(f_vect *a);

void f_vect_print(f_vect *a);
