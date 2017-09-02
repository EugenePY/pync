import ctypes


def _load_lib():
    """find the c lib from path."""
    LIB_PATH = './build/gemm_simple.dll'
    lib = ctypes.CDLL(LIB_PATH, ctypes.RTLD_GLOBAL)
    return lib, LIB_PATH


def cErrorHandle():
    """Handling c error."""
    pass


def input_handler():
    """handle input type of c func."""
    pass


def c_array(ctype, values):
    """c array."""
    return (ctype * len(values))(*values)

if __name__ == "__main__":
    _LIB, LIBPATH = _load_lib()

    def gemm():
        pass
    print _LIB.gemm
