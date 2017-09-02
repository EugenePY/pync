#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "./gemm_simple.h"
#include <Python.h>
#include <stdio.h>
#include "numpy/arrayobject.h"
#include "numpy/ndarrayobject.h"
#include "numpy/ndarraytypes.h"

// C-API
void gemm(int n, int m, int ldb, int* a, int* b, int* buffer) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < ldb; k++) {
				buffer[IDX_SCHEME(i, j, n, ldb)] +=
				    a[IDX_SCHEME(i, k, n, ldb)] *
				    b[IDX_SCHEME(k, j, ldb, m)];
			}
		}
	}
};

