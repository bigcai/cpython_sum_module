#include <Python.h>

static PyObject* sum_module_sum(PyObject* self, PyObject* args) {
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("i", a + b);
}

static PyMethodDef SumMethods[] = {
    {"sum", sum_module_sum, METH_VARARGS, "Sum two integers"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef summodule = {
    PyModuleDef_HEAD_INIT,
    "summodule",   /* name of module */
    NULL,          /* module documentation, may be NULL */
    -1,            /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    SumMethods
};

PyMODINIT_FUNC PyInit_summodule(void) {
    return PyModule_Create(&summodule);
}
