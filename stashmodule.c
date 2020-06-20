#include <Python.h>

#include "stash.h"

static PyObject *stash_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    stash_hash((char *)PyBytes_AsString((PyObject*) input), (int)PyBytes_Size((PyObject*) input), output);
#else
    stash_hash((char *)PyString_AsString((PyObject*) input), (int)PyString_Size((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef StashMethods[] = {
    { "getPoWHash", stash_getpowhash, METH_VARARGS, "Returns the proof of work hash using stash hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef StashModule = {
    PyModuleDef_HEAD_INIT,
    "stash_hash",
    "...",
    -1,
    StashMethods
};

PyMODINIT_FUNC PyInit_stash_hash(void) {
    return PyModule_Create(&StashModule);
}

#else

PyMODINIT_FUNC initstash_hash(void) {
    (void) Py_InitModule("stash_hash", StashMethods);
}
#endif
