#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned int uint;


uint *new_vector(size_t n);


uint *new_rand_vector(size_t n, size_t q);


int sample_guassian(size_t q, double sigma);


uint *new_error_vec(size_t l, size_t q, double sigma);


uint *new_matrix(size_t n, size_t l);


uint *new_rand_mat(size_t n, size_t l, size_t q);


void print_vec(uint *vec, size_t n);


void print_mat(uint *mat, size_t n, size_t l);


uint *append_vec(uint *mat, uint *vec, size_t n, size_t l);


uint *mat_vec_prod(uint *mat, uint *vec, size_t n, size_t l, size_t q);


uint *mat_sum(uint *mat_A, uint *mat_B, size_t n, size_t l, size_t q);


uint *vec_sum(uint *vec_A, uint *vec_B, size_t n, size_t q);


uint *scalar_by_vec(uint *vec, uint lambda, size_t n, size_t q);


uint *scalar_by_mat(uint *mat_A, uint lambda, size_t n, size_t l, size_t q);


size_t ceil_log2(size_t q);


uint *get_gadget_mat(size_t n, size_t l, size_t q);


char compare_vec(uint *vec_a, uint *vec_b, size_t n);