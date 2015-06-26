// Copyright (c) Arni Mar Jonsson.
// See LICENSE for details.

// The Python 2/3 compatibility code was found in cporting.rst

#include "rocksdb_ext.h"

static PyMethodDef rocksdb_extension_methods[] =
{
	{ (char*)"RepairDB",  (PyCFunction)pyrocksdb_repair_db,  METH_VARARGS | METH_KEYWORDS, (char*)pyrocksdb_repair_db_doc  },
	{ (char*)"DestroyDB", (PyCFunction)pyrocksdb_destroy_db, METH_VARARGS, (char*)pyrocksdb_destroy_db_doc },
	{NULL, NULL},
};

PyObject* rocksdb_exception = 0;

#if PY_MAJOR_VERSION >= 3

struct rocksdb_extension_state {
};

static int rocksdb_extension_traverse(PyObject* m, visitproc visit, void* arg)
{
	return 0;
}

static int rocksdb_extension_clear(PyObject* m)
{
	return 0;
}

static struct PyModuleDef rocksdb_extension_def = {
	PyModuleDef_HEAD_INIT,
	"rocksdb",
	NULL,
	sizeof(struct rocksdb_extension_state),
	rocksdb_extension_methods,
	NULL,
	rocksdb_extension_traverse,
	rocksdb_extension_clear,
	NULL
};

#define INITERROR return NULL

extern "C" PyObject* PyInit_rocksdb(void)

#else

#define INITERROR return

extern "C" void initrocksdb(void)

#endif
{
#if PY_MAJOR_VERSION >= 3
	PyObject* rocksdb_module = PyModule_Create(&rocksdb_extension_def);
#else
	PyObject* rocksdb_module = Py_InitModule3((char*)"rocksdb", rocksdb_extension_methods, 0);
#endif

	if (rocksdb_module == 0)
		INITERROR;

	// add custom exception
	rocksdb_exception = PyErr_NewException((char*)"rocksdb.RocksDBError", 0, 0);

	if (rocksdb_exception == 0) {
		Py_DECREF(rocksdb_module);
		INITERROR;
	}

	if (PyModule_AddObject(rocksdb_module, (char*)"RocksDBError", rocksdb_exception) != 0) {
		Py_DECREF(rocksdb_module);
		INITERROR;
	}

	if (PyType_Ready(&PyRocksDB_Type) < 0) {
		Py_DECREF(rocksdb_module);
		INITERROR;
	}

	if (PyType_Ready(&PyRocksDBSnapshot_Type) < 0) {
		Py_DECREF(rocksdb_module);
		INITERROR;
	}

	if (PyType_Ready(&PyWriteBatch_Type) < 0) {
		Py_DECREF(rocksdb_module);
		INITERROR;
	}

	if (PyType_Ready(&PyRocksDBIter_Type) < 0) {
		Py_DECREF(rocksdb_module);
		INITERROR;
	}

	// add custom types to the different modules
	Py_INCREF(&PyRocksDB_Type);

	if (PyModule_AddObject(rocksdb_module, (char*)"RocksDB", (PyObject*)&PyRocksDB_Type) != 0) {
		Py_DECREF(rocksdb_module);
		INITERROR;
	}

	Py_INCREF(&PyRocksDBSnapshot_Type);

	if (PyModule_AddObject(rocksdb_module, (char*)"Snapshot", (PyObject*)&PyRocksDBSnapshot_Type) != 0) {
		Py_DECREF(rocksdb_module);
		INITERROR;
	}

	Py_INCREF(&PyWriteBatch_Type);

	if (PyModule_AddObject(rocksdb_module, (char*)"WriteBatch", (PyObject*)&PyWriteBatch_Type) != 0) {
		Py_DECREF(rocksdb_module);
		INITERROR;
	}

	PyEval_InitThreads();

	#if PY_MAJOR_VERSION >= 3
	return rocksdb_module;
	#endif
}
