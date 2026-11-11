#include "vector.h"


uint *new_vector(size_t n){
	uint *vec = calloc(n, sizeof(uint));

	if (vec==NULL){
		fprintf(stderr, "new_vector allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	return vec;
}


uint *new_rand_vector(size_t n, size_t q){
	uint *vec = new_vector(n);

	for (size_t i=0; i<n; i++){
		vec[i] = rand() % q;
	}

	return vec;
}


int sample_guassian(size_t q, double sigma){
	//   Uses central limit theorem to produce a random number 
	// generator with the normal/gaussian distribution (0, sigma)

	int n = 20;
	double Sn = 0;

	for (int i = 0; i<n; i++){
		Sn += rand()%2;
	}

	Sn *= 2;
	Sn -= n;
	Sn *= sigma/sqrt(n);

    int res = (int) round(Sn);

    if (res < 0)
        return (q - ((-res) % q)) % q;

    return res % q;
}


uint *new_error_vec(size_t l, size_t q, double sigma){
	uint *error_vec = new_vector(l);

	for (size_t i=0; i<l; i++){
		error_vec[i] = sample_guassian(q, sigma);
	}

	return error_vec;
}


uint *new_matrix(size_t n, size_t l){
	uint *mat = calloc(n*l, sizeof(uint));

	if (mat==NULL){
		fprintf(stderr, "new_vector allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	
	return mat;
}

uint *new_rand_mat(size_t n, size_t l, size_t q){
	uint *mat = new_matrix(n, l);

	for (size_t i=0; i<n*l; i++){
		mat[i] = rand() % q;
	}

	return mat;
}


void print_vec(uint *vec, size_t n){
	printf("[");
	for (size_t i = 0; i<n; i++){
		printf("%i, ", vec[i]);
	}
	printf("\b\b]\n");
}


void print_mat(uint *mat, size_t n, size_t l){
	printf("[");
	for (size_t j = 0; j<n; j++){
		printf("[");
		for (size_t i = 0; i<l; i++){
			printf("%i, ", mat[i*n + j]);
		}
		printf("\b\b]");
		if (j<(n-1))
			printf("\n");
	}
	printf("]\n");
}


uint *append_vec(uint *mat, uint *vec, size_t n, size_t l){

	uint *res = new_matrix(n+1, l);

	for (size_t i = 0; i<n*l; i++){
		res[i] = mat[i];
	} 

	for (size_t i = 0; i<l; i++){
		res[n*l+i] = vec[i];
	}

	return res;
}

uint *mat_vec_prod(uint *mat, uint *vec, size_t n, size_t l, size_t q){

	uint *res = new_vector(l);

	for (size_t i=0; i<l; i++){
		for (size_t j=0; j<n; j++){
			res[i] += (mat[j*l+i]*vec[j]) % q;
		}
		res[i] = res[i]%q;
	}

	return res;
}

uint *mat_sum(uint *mat_A, uint *mat_B, size_t n, size_t l, size_t q){
	uint *sum = new_matrix(n,l);

	for (size_t i=0; i<n*l; i++){
		sum[i] = (mat_A[i] + mat_B[i]) % q;
	}

	return sum;
}


uint *vec_sum(uint *vec_A, uint *vec_B, size_t n, size_t q){
	uint *sum = new_vector(n);

	for (size_t i=0; i<n; i++){
		sum[i] = (vec_A[i] + vec_B[i]) % q;
	}

	return sum;
}


uint *scalar_by_vec(uint *vec, uint lambda, size_t n, size_t q){
	uint *vec_scalar = new_vector(n);

	for (size_t i=0; i<n; i++){
		vec_scalar[i] = (vec[i]*lambda) % q;
	}

	return vec_scalar;	
}


uint *scalar_by_mat(uint *mat_A, uint lambda, size_t n, size_t l, size_t q){
	uint *mat_scalar = new_matrix(n,l);

	for (size_t i=0; i<n*l; i++){
		mat_scalar[i] = (mat_A[i]*lambda) % q;
	}

	return mat_scalar;	
}


size_t ceil_log2(size_t q){
    size_t k = 0;
    q--;

    while (q > 0) {
        q >>= 1;
        k++;
    }

    return k;
}


uint *get_gadget_mat(size_t n, size_t l, size_t q){
	uint *G = new_matrix(l, n+1);
	size_t x;

	for (size_t i=0; i<n+1; i++){
		x = i*l+ceil_log2(q-1)*i;
		for (size_t j=1; j<ceil_log2(q)+1; j++){
			G[x+j-1] = 1<<(j-1);
		}
	}
	return G;
}


char compare_vec(uint *vec_a, uint *vec_b, size_t n){
	for (size_t i=0; i<n; i++){
		if (vec_a[i] != vec_b[i])
			return 0;
	}
	return 1;
}