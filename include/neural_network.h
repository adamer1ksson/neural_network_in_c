#pragma once
#include "../include/base.h"
#include "../include/matrix.h"
#include "../include/arena.h"

typedef f32(*loss_func)(f_matrix*, f_matrix*);

typedef struct {
    f_matrix weights;
    f_matrix bias;
    f_func activation;
    f_func activation_derivative;
    u32 dim_in;
    u32 dim_out;
} f_layer;

typedef struct {
    f_layer* layers;
    u32 num_layers;
    loss_func E;
} neural_network;

f_matrix create_matrix_ones(mem_arena* arena, u64 rows, u64 cols);

f_layer create_layer(mem_arena* arena, u32 dim_in, u32 dim_out, f_func activation, f_func activation_derivative);
void init_layer_uniform(f_layer *L, f32 min, f32 max);
void init_layer_normal(f_layer *L, f32 mean, f32 std_dev);
void run_layer(f_matrix *out, f_layer *L, f_matrix* in);

neural_network create_neural_network(f_layer* layers, u32 num_layers, loss_func E);
void run_neural_network(f_matrix* out, neural_network* nn, f_matrix* in);
f_matrix* run_neural_network_all_outputs(mem_arena* arena, f_matrix* out, neural_network* nn, f_matrix* in);

void back_propagation(mem_arena* arena, neural_network* nn, f_matrix* nn_all_outputs, f_matrix* correct_out);
