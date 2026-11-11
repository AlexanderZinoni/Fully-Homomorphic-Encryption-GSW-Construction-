#include "vector.h"
#include "GSW.h"

int main(){
	// Initialise values
	size_t n = 2; 
	size_t q = 1<<3;
	size_t l = (n+1) * ceil_log2(q);

	uint *key = key_gen(n,q);

	char b = 1;

	uint *C = enc_bit(n,q,key,b);
	printf("\n");
	print_mat(C,l,n+1);
}