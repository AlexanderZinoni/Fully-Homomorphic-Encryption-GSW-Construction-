#include "vector.h"
#include "GSW.h"

int main(){
	// Initialise values
	size_t n = 2; 
	size_t q = 1<<4;
	size_t l = (n+1) * ceil_log2(q);

	uint *key = key_gen(n,q);

	char b = 1;

	printf("Encrypting: %i \n", b);

	uint *C = enc_bit(n,q,key,b);
	printf("\n");

	printf("Ciphertext matrix: \n");
	print_mat(C,l,n+1);

	char b_2 = dec_bit(n, q, C, key);
	printf("\nDecryption: %i \n", b_2);
}