#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "numpy/arrayobject.h"
#include <Python.h> // coherient with linux

#define C_IDX_SCHEME(i, j, M, N) i * N  + j
// simple gemm for int
void gemm(int n, int m, int ldb, int* a, int* b, int* buffer); 

static PyObject* int_gemm(PyObject* self, PyObject* args);

