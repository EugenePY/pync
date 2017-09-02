#include "./gemm_simple.h"
#include <Python.h>
#include <stdio.h>
#include "numpy/__ufunc_api.h"
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

PyArrayObject* int_gemm(PyArrayObject* a, PyArrayObject* b) {
	int n = PyArray_DIM(a, 0);
	int m = PyArray_DIM(b, 1);
	int ldb = PyArray_DIM(b, 0);
	int result[n * m];
	PyArrayObject* out_array;

	gemm(n, m, ldb, PyArray_DATA(a), PyArray_DATA(b), result);
	return out_array;
};

//PyMethodDef GEMM[] = {
 //   {"int_gemm", int_gemm, METH_VARARGS, "evaluate the gemm in int"},
 //   {NULL, NULL, 0, NULL}};

//PyMODINIT_FUNC initcos_module_np(void) {
//	(void)Py_InitModule("int_gemm", GEMM);
	//* IMPORTANT: this must be called */
//	import_array();
//}
