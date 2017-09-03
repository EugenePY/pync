import c_modules.gemm as gemm
import numpy as np


def test():
    """simple test."""

    m = 220
    n = 200
    ldb = 300
    a = np.array(np.arange(m*ldb).reshape((m, ldb)).astype(np.intc))
    b = np.array(np.arange(ldb*n).reshape((ldb, n)).astype(np.intc))
    c = gemm.int_gemm(a, b)
    assert(np.all(np.isclose(c, a.dot(b))))
    print("Testing Pass")

if __name__ == '__main__':
    test()
