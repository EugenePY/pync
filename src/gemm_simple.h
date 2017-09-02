#include "numpy/arrayobject.h"
#include <Python.h> // coherient with linux

#define IDX_SCHEME(i, j, N, M) j * (N)  + i
// simple gemm for int
void gemm(int n, int m, int ldb, int* a, int* b, int* buffer); 

PyArrayObject* int_gemm(PyArrayObject* a, PyArrayObject* b);
