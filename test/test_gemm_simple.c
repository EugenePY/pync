#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include "./src/gemm_simple.h"
#include "numpy/arrayobject.h"
#include "numpy/ndarraytypes.h"
#include "numpy/ndarrayobject.h"
#include "numpy/ufuncobject.h"


static void printf_1_array(int* buffer, int stride, int ndim) {
	for (int i = 0; i < stride; ++i) {
		for (int j = 0; j < ndim; ++j) {
			printf("%i", buffer[IDX_SCHEME(i, j, stride, ndim)]);
			printf(" ");
		}
		printf("\n");
	}
}
// static void find_prime(int num_elements, int* buffer);
//

int main() {
	// routine buffer & data
	int m = 5;
	int n = 6;
	int ldb = 3;
	int a[m * ldb];
	int b[ldb * n];
	int result[m * n];

	for (int i = 0; i < m * ldb; ++i) {
		a[i] = i;
	}
	for (int i = 0; i < ldb * n; ++i) {
		b[i] = i;
	}


	printf("==== Matrix a ====\n");
	printf_1_array(a, m, ldb);

	printf("==== Matrix b ====\n");
	printf_1_array(b, ldb, n);

	// actural computions
	gemm(m, n, ldb, a, b, result);
	printf("==== Matrix result ====\n");
	printf_1_array(result, m, n);


	return 0;
}
