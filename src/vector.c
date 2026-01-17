#include "stdio.h"
#include "math.h"

#include "../include/base.h"
#include "../include/vector.h"

void f_vect_add(f_vect *out, f_vect *a, f_vect *b) {
    if (out->len != a->len || out->len != b->len || a->len != b->len){
        fprintf(stderr, "Adding vectors of different lengths not allowed.\n");
        return;
    }
    u64 length = out->len;
    for (u64 i = 0; i < length; i++) {
        out->data[i] = a->data[i] + b->data[i];
    }
    return;
}
void f_vect_sub(f_vect *out, f_vect *a, f_vect *b) {
    if (out->len != a->len || out->len != b->len || a->len != b->len){
        fprintf(stderr, "Subtracting vectors of different lengths not allowed.\n");
        return;
    }
    u64 length = out->len;
    for (u64 i = 0; i < length; i++) {
        out->data[i] = a->data[i] - b->data[i];
    }
    return;

}
f32 f_vect_dot(f_vect *a, f_vect *b){
    if (a->len != b->len){
        fprintf(stderr, "Dot product with vectors of different lengths not allowed.\n");
        return 0.0f;
    }
    u64 length = a->len;
    f32 sum = 0;
    for (u64 i = 0; i < length; i++) {
        sum += a->data[i] * b->data[i];
    }
    return sum;
}

f32 f_vect_norm(f_vect *a) {
    u64 length = a->len;
    f32 sum = 0;
    for (u64 i = 0; i < length; i++) {
        sum += a->data[i] * a->data[i];
    }
    return sqrtf(sum);
}

f_vect f_vect_create(mem_arena* arena, u64 len) {
    f_vect v;
    v.len = len;
    v.data = PUSH_N_STRUCTS(arena, f32, len);
    return v;
}

void f_vect_print(f_vect *a) {
    printf("\n (");
    for (u64 i = 0; i < a->len; i++) {
        printf(" %.2f ", a->data[i]);
    } 
    printf(")^T\n");
}
