#ifndef PY_TYPE_H
#define PY_TYPE_H

#include <stdbool.h>

typedef enum {
    PY_INT,
    PY_DECIMAL,
    PY_STRING,
    PY_BOOL,
    PY_NONE,
} PyType;

typedef struct PyObject {
    PyType type;
    union {
        int integer;
        double decimal;
        char *string;
        bool boolean;
    } as;
} PyObject;

PyObject py_int(int value);
PyObject py_decimal(double value);
PyObject py_string(const char *value);
PyObject py_bool(bool value);
PyObject py_none();

void py_free(PyObject *object);

#endif
