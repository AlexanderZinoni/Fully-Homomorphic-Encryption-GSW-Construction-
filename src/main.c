#include "vector.h"
#include "GSW.h"
#include <time.h>


int main(){
	// Initialise values
	size_t n = 640; 
	size_t q = 1<<15;
	size_t l = (n+1) * ceil_log2(q);
	double sigma = 2.3;


	printf("Parameters: n = %li, q = 2^%li, l = %li, error = %.1f\n", n,ceil_log2(q),l, sigma);

	uint *key = key_gen(n,q);

	char b = 1;
	char b2 = 0;

	printf("Encrypting: %i -> C1\n", b);
	clock_t start_c1 = clock();
	uint *C = enc_bit(n,q,key,b,sigma);
	clock_t end_c1 = clock();

	printf("Encrypting: %i -> C2\n", b2);
	clock_t start_c2 = clock();
	uint *C2 = enc_bit(n,q,key,b2,sigma);
	clock_t end_c2 = clock();

	//printf("Ciphertext matrix: \n");
	//print_mat(C,l,n+1);

	clock_t start_sum = clock();
	uint *C_sum = hom_sum(n,q,C,C2);
	clock_t end_sum = clock();

	clock_t start_dec = clock();
	char b_2 = dec_bit(n, q, C_sum, key);
	clock_t end_dec = clock();
	printf("Decryption of C1 XOR C2: %i \n", b_2);

	printf("\n");
	printf("Times:\n");
	printf("Encryption of C1 : %fs\n", (float)(end_c1 - start_c1) / CLOCKS_PER_SEC);
	printf("Encryption of C2 : %fs\n", (float)(end_c2 - start_c2) / CLOCKS_PER_SEC);
	printf("C1 + C2 : %fs\n", (float)(end_sum - start_sum) / CLOCKS_PER_SEC);
	printf("Decryption of C1+C2 : %fs\n", (float)(end_dec - start_dec) / CLOCKS_PER_SEC);

	free(key);
	free(C);
	free(C2);
	free(C_sum);
}