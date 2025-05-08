#define PY_SSYZE_T_CLEAN
#include <Python.h>

// 클래스 인스턴스 구조체
typedef struct {
    PyObject_HEAD PyObject *name;
} HelloObject;


// def main(); 파이썬의 리턴 타입은 모두 타입이 PyObject로 통일되어서 C에서 앞에 선언하던 리턴 타입은 안써주게 되었다
static PyObject *Hello_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    HelloObject *self;
    self = (HelloObject *)type->tp_alloc(type, 0);
    if (self != NULL){
        self->name = PyUnicode_FromString("");
        if (self->name == NULL){
            Py_DECREF(self);
            return NULL;
        }
    }
    return (PyObject *)self;
}

// init
static int Hello_init(HelloObject *self, PyObject *args, PyObject *kwds){
    PyObject *name = NULL;
    static char *kwlist[] = {"name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "U", kwlist, &name)){
        return -1;
    }

    Py_INCREF(name);
    Py_DECREF(self->name);
    self->name = name;
    return 0;
}

// python's def hello_greet(); -> made by c code
static PyObject *Hello_greet(HelloObject *self, PyObject *Py_UNUSED(ignored)){
    return PyUnicode_FromFormat("hello, %U!", self->name);
}

static PyMethodDef Hello_methods[] = {
    {"greet", (PyCFunction)Hello_greet, METH_NOARGS, "Greet the person."},
    {NULL}
};

static PyTypeObject HelloType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "mymodule.hello",
    .tp_basicsize = sizeof(HelloObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Hello objects",
    .tp_new = Hello_new,
    .tp_init = (initproc)Hello_init,
    .tp_dealloc = (destructor)PyObject_Del,
    .tp_methods = Hello_methods,
};

// 모듈 정의
static PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "mymodule",
    .m_doc = "C type module example",
    .m_size = -1,
};

// 모듈 초기화
PyMODINIT_FUNC PyInit_mymodule(void){
    PyObject *m;
    if (PyType_Ready(&HelloType) < 0){
        return NULL;
    }

    m = PyModule_Create(&mymodule);
    if (m == NULL){
        return NULL;
    }

    Py_INCREF(&HelloType);
    if (PyModule_AddObject(m, "Hello", (PyObject *)&HelloType) < 0)    {
        Py_DECREF(&HelloType);
        Py_DECREF(m);
        return NULL;
    }
    return m;
}

// .os를 생성하는건 좋은데 자동적으로 인스톨이 되야함
// setup python tool을 활용한 자동화를 시킨다