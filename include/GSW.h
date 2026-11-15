#include "vector.h"

uint *key_gen(size_t n, size_t q);


uint *enc_bit(size_t n, size_t q, uint *key, char mu, double sigma);


char dec_bit(size_t n, size_t q, uint *C, uint *key);


uint *hom_sum(size_t n, size_t q, uint *C1, uint *C2);
