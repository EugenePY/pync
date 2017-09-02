/* some macros and meta variables
 */
#include <Python.h>
#include "numpy/arrayobject.h"

#define MAKE_CONTAINER(type) typedef struct MAKE_NAME(Container_, type) { type data; } MAKE_NAME(Container_, type)}

