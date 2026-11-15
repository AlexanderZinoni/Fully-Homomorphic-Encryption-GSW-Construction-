#include "GSW.h"

uint *key_gen(size_t n, size_t q){
	uint *key = new_vector(n);

	for (size_t i = 0; i<n; i++){
		key[i] = rand() % q;
	}

	return key;
}


uint *s_from_key(uint *key, size_t n){
	uint *s = new_vector(n+1);

	for (size_t i=0; i<n; i++){
		s[i] = key[i];
	}

	s[n] = 1;

	return s;
}


char check_correctness(uint *A, uint *key, uint *e, size_t n, size_t l, size_t q){

	uint *s = s_from_key(key, n);
	uint *test = mat_vec_prod(A, s, n+1, l, q);
	free(s);

	if (compare_vec(test, e, l)){
		free(test);
		return 1;
	}

	free(test);
	return 0;

}


uint *enc_bit(size_t n, size_t q, uint *key, char mu, double sigma){
	size_t l = (n+1) * ceil_log2(q);

	uint *A = new_rand_mat(l, n, q);
	uint *e = new_error_vec(l,q,sigma);

	uint *s_neg = scalar_by_vec(key,-1,n,q);

	uint *A_key = mat_vec_prod(A, s_neg, n, l, q);
	uint *v = vec_sum(e,A_key,l,q);
	free(s_neg);
	free(A_key);

	uint *B = append_vec(A, v, n, l);
	free(A);
	free(v);

	uint *G = get_gadget_mat(n,l,q);
	uint *G_mu = scalar_by_vec(G, mu, l*(n+1), q);
	free(G);

	uint *C = mat_sum(B, G_mu, n+1, l, q);
	free(B);

	// Checking the correctness of C by computing the decryption invariant.
	uint *s = s_from_key(key,n);
	uint *G_mu_s = mat_vec_prod(G_mu, s, n+1, l, q);
	uint *dec_inv = vec_sum(e, G_mu_s, l, q);
	free(s);
	free(G_mu_s);
	free(e);
	free(G_mu);

	if (!check_correctness(C,key,dec_inv,n,l,q))
		printf("RESULT INCORECT\n");
	free(dec_inv);

	return C;
}


char dec_bit(size_t n, size_t q, uint *C, uint *key){
	size_t l = (n+1) * ceil_log2(q);
	uint *s = s_from_key(key, n);

	uint *Cs = mat_vec_prod(C, s, n+1, l, q);
	free(s);

	uint top = Cs[l-1];
	free(Cs);

	char bit = (top > q/4) && (top < q - q/4);

	return bit;
}


uint *hom_sum(size_t n, size_t q, uint *C1, uint *C2){
	size_t l = (n+1) * ceil_log2(q);
	return vec_sum(C1, C2, (n+1)*l, q);
}