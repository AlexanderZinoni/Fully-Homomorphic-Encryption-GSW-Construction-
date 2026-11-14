#include "vector.h"

uint *key_gen(size_t n, size_t q);


uint *enc_bit(size_t n, size_t q, uint *key, char mu);


char dec_bit(size_t n, size_t q, uint *C, uint *key);