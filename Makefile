GCC := gcc
G++ := g++

## OS meta
LDSUFFIX := dll

## libs
NUMPY_INCLUDE := /Library/Python/2.7/site-packages/numpy/core/include/

PY_HEADER := /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
LIBS = /Library/Python/2.7/site-packages/numpy/core/lib/

# simple flags
C_SRC = $(wildcard src/*.c)
CFLAG = -std=c99 -Wall -g  -O2 -I./ -I${NUMPY_INCLUDE} -isystem ${PY_HEADER} -fPIC 

LDFLAG := -pthread -lm -ldl -L${LIBS} -lpython2.7

# build target
OBJS := build/gemm_simple.$(LDSUFFIX)

# compile with python 
all: $(OBJS)
test: test/test_gemm_simple.out

build/%.dll: build/%.o 
	@mkdir -p $(@D)
		$(GCC) $(CFLAGS) -shared $(LDFLAG) -o $@ $(filter %.o %.a, $^)

build/%.o: src/%.c
	@mkdir -p $(@D)
	$(GCC) $(CFLAG) -MM -MT build/$*.o $< >build/$*.d
	$(GCC) -c $(CFLAG) -c $< -o $@

# testing in C
test/test_%: test/test_%.o
	$(GCC) $(OBJS) $< -o $@

test/test_%.o: test/test_%.c
	$(GCC) -c $(CFLAG) -c $< -o $@

clean:
	@rm -rf build
	@rm ./test/*.out
