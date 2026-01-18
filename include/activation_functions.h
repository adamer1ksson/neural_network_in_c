#pragma once
#include "../include/base.h"
#include "../include/matrix.h"

f32 f_square(f32 x);

f32 f_ReLU(f32 x);
f32 f_sigmoid(f32 x);
f32 f_tanh(f32 x);

f32 f_ReLU_derivative(f32 x);
f32 f_sigmoid_derivative(f32 x);
f32 f_tanh_derivative(f32 x);
f32 f_sigmoid_derivative_from_value(f32 x);
f32 f_tanh_derivative_from_value(f32 x);

void f_softmax(f_matrix *a);

