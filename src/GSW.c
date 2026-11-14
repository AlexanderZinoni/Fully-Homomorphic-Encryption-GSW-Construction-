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

	if (compare_vec(test, e, l)){
		free(test);
		free(s);
		return 1;
	}

	free(test);
	free(s);
	return 0;

}


uint *enc_bit(size_t n, size_t q, uint *key, char mu){
	size_t l = (n+1) * ceil_log2(q);

	uint *A = new_rand_mat(l, n, q);
	uint *e = new_error_vec(l,q,1);

	uint *v = mat_vec_prod(A, scalar_by_vec(key,-1,n,q), n, l, q);
	v = vec_sum(e,v,l,q);

	A = append_vec(A, v, n, l);

	if (!mu){
		//printf("not mu\n");
		if (!check_correctness(A,key,e,n,l,q))
			printf("RESULT INCORECT\n");
		free(v);
		free(e);
		return A;
	}

	uint *G = get_gadget_mat(n,l,q);
	A = mat_sum(A, G, n+1, l, q);
	e = vec_sum(e, mat_vec_prod(G, s_from_key(key,n), n+1, l, q), l, q);
	if (!check_correctness(A,key,e,n,l,q))
		printf("RESULT INCORECT\n");
	free(v);
	free(e);
	return A;
}


char dec_bit(size_t n, size_t q, uint *C, uint *key){
	size_t l = (n+1) * ceil_log2(q);
	key = s_from_key(key, n);

	uint *Cs = mat_vec_prod(C, key, n+1, l, q);
	//print_vec(Cs,l);

	uint max_magnitude = q>>2; // or q/4

	for (size_t i=0; i<l; i++){
		//printf("%i > %i AND %i < %li\n",Cs[i],max_magnitude, Cs[i], q-max_magnitude);

		if ( (Cs[i]>max_magnitude) && (Cs[i]<q-max_magnitude) ){
			return 1;
		}
	}

	return 0;
}