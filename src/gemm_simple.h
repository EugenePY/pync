#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "numpy/arrayobject.h"
#include <Python.h> // coherient with linux

#define IDX_SCHEME(i, j, N, M) j * (N)  + i
// simple gemm for int
void gemm(int n, int m, int ldb, int* a, int* b, int* buffer); 

// PyArrayObject* int_gemm(PyArrayObject* a, PyArrayObject* b);
static PyObject* int_gemm(PyObject* self, PyObject* args) {
	/*int n = PyArray_DIM(a, 0);
	int m = PyArray_DIM(b, 1);
	int ldb = PyArray_DIM(b, 0);
	int result[n * m];
	PyArrayObject* out_array;

	gemm(n, m, ldb, PyArray_DATA(a), PyArray_DATA(b), result);

	PyObject* a_np_array_ptr;
	npy_intp dims[2];
	dims[0] = m;
	dims[1] = ldb;
	// set items
	// initial the module (if not segfault happen will.)
	a_np_array_ptr = PyArray_New(&PyArray_Type, 2, dims, NPY_INT, NULL,
					a, 0, NPY_ARRAY_CARRAY, NULL);

	return out_array;
	*/
	double p;

	/* This parses the Python argument into a double */
	if (!PyArg_ParseTuple(args, "d", &p)) {
		return NULL;
	}

	/* THE ACTUAL LOGIT FUNCTION */
	p = p / (1 - p);
	p = log(p);

	/*This builds the answer back into a python object */
	return Py_BuildValue("d", p);
};

PyMethodDef pyarray[] = {
    {"int_gemm", int_gemm, METH_VARARGS, "evaluate the gemm in int"},
    {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC initarray(void) {
	(void)Py_InitModule("array", pyarray);
	//* IMPORTANT: this must be called */
	import_array();
}
