#include "math.h"

#include "../include/activation_functions.h"
#include "../include/base.h"
#include "../include/matrix.h"
#include "../include/linalg.h"

f32 f_square(f32 x) {
    return x*x;
}

f32 f_ReLU(f32 x) {
    return MAX(0.0f, x);
}

f32 f_sigmoid(f32 x) {
    return 1.0f / (1.0f + (f32)exp( -(f64)x ) );    
}

f32 f_tanh(f32 x) {
    return (f32)tanh( (f64)x );
}

f32 f_ReLU_derivative(f32 x) {
    if (x >= 0.0f) {
        return 1.0f;
    }
    return 0.0f;
}

f32 f_sigmoid_derivative(f32 x) {
    return f_sigmoid(x) * (1.0f - f_sigmoid(x));
}

f32 f_tanh_derivative(f32 x) {
    return 1.0f - f_square(f_tanh(x));
}

void f_softmax(f_matrix *a) {
    f_matrix_transpose(a); //rows are now the prob. vectors
    u64 rows = a->rows;
    u64 cols = a->cols;
    for (u64 i = 0; i < rows; i++) {
        f32 sum = 0.0f;
        for (u64 j = 0; j < cols; j++) {
            f32 val = (f32)exp((f64) a->data[i*cols + j]);
            a->data[i*cols + j] = val;
            sum += val; 
        }
        f_matrix_scale_row(a, 1.0f/sum, i);
    }
    f_matrix_transpose(a);
    return;
}
