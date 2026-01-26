#include "stdio.h"

#include "../include/base.h"
#include "../include/neural_network.h"
#include "../include/matrix.h"
#include "../include/random.h"

f_matrix create_matrix_ones(mem_arena* arena, u64 rows, u64 cols) {
    f_matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = PUSH_N_STRUCTS(arena, f32, rows*cols);
    for (u32 i = 0; i < rows; i++) {
        for (u32 j = 0; j < cols; j++) {
            mat.data[i*cols + j] = 1.0f;
        }
    }
    return mat;
}

f_layer create_layer(mem_arena* arena, u32 dim_in, u32 dim_out, f_func activation, f_func activation_derivative) {
    f_layer layer;
    layer.dim_in = dim_in;
    layer.dim_out = dim_out;
    layer.weights = f_matrix_create(arena, (u64)dim_out, (u64)dim_in);
    layer.bias = f_matrix_create(arena, dim_out, 1);
    layer.activation = activation;
    layer.activation_derivative = activation_derivative;
    return layer;
}

void init_layer_uniform(f_layer *L, f32 min, f32 max) {
    u32 rows = L->dim_out;
    u32 cols = L->dim_in;
    for (u32 i = 0; i < rows; i++) {
        for (u32 j = 0; j < cols; j++) {
            L->weights.data[i*cols + j] = uniform(min, max);
        }
    } 
    return;
}

void init_layer_normal(f_layer *L, f32 mean, f32 std_dev) {
    u32 rows = L->dim_out;
    u32 cols = L->dim_in;
    for (u32 i = 0; i < rows; i++) {
        for (u32 j = 0; j < cols; j++) {
            L->weights.data[i*cols + j] = normal_dist(mean, std_dev);
        }
    } 
    return;
}

void run_layer(f_matrix *out, f_layer *L, f_matrix* in) {
    f_matrix_mult(out, &L->weights, in, false, false);
    f_matrix_add(out, out, &L->bias);
    f_matrix_apply_func(L->activation, out);
}

neural_network create_neural_network(f_layer* layers, u32 num_layers, loss_func E) {
    neural_network nn;
    nn.layers = layers;
    nn.num_layers = num_layers;
    nn.E = E;
    return nn;
}

void run_neural_network(f_matrix* out, neural_network* nn, f_matrix* in) {
    for (u32 i = 0; i < nn->num_layers; i++) {
        run_layer(out, &nn->layers[i], in);
    }  
}

f_matrix* run_neural_network_all_outputs(mem_arena* arena, f_matrix* out, neural_network* nn, f_matrix* in) {
    f_matrix* all_outputs_array = PUSH_N_STRUCTS(arena, f_matrix, nn->num_layers+1);
    f_matrix_copy(&(all_outputs_array[0]), in);
    for (u32 i = 1; i <= nn->num_layers; i++) {
        run_layer(out, &nn->layers[i], in);
        f_matrix_copy(&(all_outputs_array[i]), out);
    }
    return all_outputs_array; 
}

void back_propagation(mem_arena* arena, neural_network* nn, f_matrix* nn_all_outputs, f_matrix* correct_out) {
    u64 data_points = correct_out->cols;
    f_matrix delta = f_matrix_create(arena, correct_out->rows, correct_out->cols);
    // assume softmax and cross entropy loss for now
    f_matrix_sub(&delta, &(nn_all_outputs[nn->num_layers]), correct_out);
    for (u32 i = nn->num_layers - 1; i >= 0; i--) {
    }
        
        

}







