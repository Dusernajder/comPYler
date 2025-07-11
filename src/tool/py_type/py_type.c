#include <stdlib.h>
#include <string.h>

#include "utils/utils.h"
#include "py_type.h"

PyObject *py_int(int value){
    PyObject *object = check_malloc(malloc(sizeof(PyObject)));
    object->type = PY_INT;
    object->as.integer = value;
    
    return object;
}


PyObject *py_decimal(double value){
    PyObject *object = check_malloc(malloc(sizeof(PyObject)));
    object->type = PY_DECIMAL;
    object->as.decimal = value;
    
    return object;
}


PyObject *py_string(const char *value) {
    PyObject *object = check_malloc(malloc(sizeof(PyObject)));
    object->type = PY_STRING;
    object->as.string = strdup(value);

    return object;
}


PyObject *py_bool(bool value){
    PyObject *object = check_malloc(malloc(sizeof(PyObject)));
    object->type = PY_BOOL;
    object->as.boolean = value;
    
    return object;
}


PyObject *py_none(){
    PyObject *object = check_malloc(malloc(sizeof(PyObject)));
    object->type = PY_NONE;
    
    return object;
}

void py_free(PyObject *object){
    if (!object) return;
    if (object->type == PY_STRING){
        free(object->as.string);
    }
}
