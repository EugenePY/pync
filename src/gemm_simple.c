#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "./gemm_simple.h"
#include <Python.h>
#include <math.h>
#include <stdio.h>
#include "numpy/arrayobject.h"
#include "numpy/ndarrayobject.h"
#include "numpy/ndarraytypes.h"
#include "numpy/utils.h"

// C-API
void gemm(int m, int n, int ldb, int* a, int* b, int* buffer) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < ldb; k++) {
				if (k == 0) {
					buffer[C_IDX_SCHEME(i, j, m, n)] =
					    a[C_IDX_SCHEME(i, k, m, ldb)] *
					    b[C_IDX_SCHEME(k, j, ldb, n)];
				} else {
					buffer[C_IDX_SCHEME(i, j, m, n)] +=
					    a[C_IDX_SCHEME(i, k, m, ldb)] *
					    b[C_IDX_SCHEME(k, j, ldb, n)];
				}
			}
		}
	}
};

static void printf_1_array(int* buffer, int m, int n) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%i", buffer[C_IDX_SCHEME(i, j, m, n)]);
			printf(" ");
		}
		printf("\n");
	}
}

static void printf_2D_PyArrayObj(PyArrayObject* arr, int m, int n) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%i", ((int*)PyArray_DATA(
					 arr))[C_IDX_SCHEME(i, j, m, n)]);
			printf(" ");
		}
		printf("\n");
	}
}

static PyObject* int_gemm(PyObject* self, PyObject* args) {
	PyObject *arg1 = NULL, *arg2 = NULL;
	PyArrayObject *a = NULL, *b = NULL;

	if (!PyArg_ParseTuple(args, "O!O!", &PyArray_Type, &arg1, &PyArray_Type,
			      &arg2))
		return NULL;
	if (NULL == arg1) {
		printf("Error1");
		exit(0);
	}
	if (NULL == arg2) {
		printf("Error2");
		exit(0);
	}

	a = (PyArrayObject*)PyArray_FROM_OTF(arg1, NPY_INT, NPY_ARRAY_IN_ARRAY);
	b = (PyArrayObject*)PyArray_FROM_OTF(arg2, NPY_INT, NPY_ARRAY_IN_ARRAY);

	int m = PyArray_DIM(a, 0);
	int n = PyArray_DIM(b, 1);
	int ldb = PyArray_DIM(b, 0);
	int result[m * n];
	// the memory alignment problem

	// for (int i = 0; i < m; ++i) {
	//	printf("%i", *(s + i));
	//}
	int* buffer_a = PyArray_DATA(a);
	int* buffer_b = PyArray_DATA(b);

	gemm(m, n, ldb, buffer_a, buffer_b, result);

	PyObject *a_np_array_ptr;

	npy_intp dims[2];
	dims[0] = m;
	dims[1] = n;
	// set items
	// initial the module (if not segfault happen will.)
	a_np_array_ptr = PyArray_SimpleNew(
	    2, dims, NPY_INT);

	//printf_1_array(PyArray_DATA(a_np_array_ptr), m, n);
	Py_INCREF(a_np_array_ptr);
	memcpy(PyArray_DATA(a_np_array_ptr), result, m*n*sizeof(int));
	return PyArray_FROM_O(a_np_array_ptr);
};

PyMethodDef IntGEMM[] = {
    {"int_gemm", int_gemm, METH_VARARGS, "evaluate the gemm in int"},
    {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC initgemm(void) {
	(void)Py_InitModule("gemm", IntGEMM);
	//* IMPORTANT: this must be called */
	import_array();
}
