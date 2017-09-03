import numpy as np
import c_modules.gemm as gemm


def test():
    """simple test."""

    m = 2200
    n = 200
    ldb = 300
    a = np.array(np.arange(m*ldb).reshape((m, ldb)).astype(np.intc))
    b = np.array(np.arange(ldb*n).reshape((ldb, n)).astype(np.intc))
    c = gemm.int_gemm(a, b)
    print np.all(np.isclose(c, a.dot(b)))

if __name__ == '__main__':
    test()
