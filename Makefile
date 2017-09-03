GCC := gcc
G++ := g++

## OS meta
LDSUFFIX := dylib

## libs
NUMPY_INCLUDE := /Library/Python/2.7/site-packages/numpy/core/include/

PY_HEADER := /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7/
LIBS = /Library/Python/2.7/site-packages/numpy/core/
PY_LIBS = /System/Library/Frameworks/Python.framework/Versions/2.7/lib/

# simple flags
C_SRC = $(wildcard src/*.c)
CFLAG = -std=c99 -Wall -g  -O2 -I./ -I${NUMPY_INCLUDE} -isystem ${PY_HEADER} -fPIC 

LDFLAG := -pthread -lm -ldl -L${LIBS} -lpython2.7
# build target
OBJS := build/gemm_simple.$(LDSUFFIX)

# compile with python 

all: $(OBJS)
test: test/test_gemm_simple.out

python:
	python setup.py build --inplace 

build/%.dylib: build/%.o 
	@mkdir -p $(@D)
		$(GCC) $(CFLAGS) -shared $(LDFLAG) -o $@ $(filter %.o %.a, $^)

build/%.o: src/%.c
	@mkdir -p $(@D)
	$(GCC) $(CFLAG) -MM -MT build/$*.o $< >build/$*.d
	$(GCC) -c $(CFLAG) -c $< -o $@

# testing in C
test/test_%: test/test_%.o
	$(GCC) -lpython2.7 $(OBJS) $< -o $@

test/test_%.o: test/test_%.c
	$(GCC) -c $(CFLAG) -c $< -o $@

# testing in Python
test_python:
	PYTHONPATH='./' python python/test.py


clean:
	@rm -rf build
	@rm ./test/*.out
