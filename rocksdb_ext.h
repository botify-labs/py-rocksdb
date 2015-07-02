// Adapted from py-leveldb,
// which is Copyright (c) Arni Mar Jonsson.
// See LICENSE for details.

#ifndef __ROCKSDB__MODULE__H__
#define __ROCKSDB__MODULE__H__

extern "C" {
#include <Python.h>

#include "structmember.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
}

#include <rocksdb/db.h>
#include <rocksdb/write_batch.h>
#include <rocksdb/comparator.h>
#include <rocksdb/cache.h>
#include <rocksdb/utilities/leveldb_options.h>
#include <vector>

typedef struct {
	PyObject_HEAD

	// object is open if all of these are non-null,
	// once an object has been closed, it can not be re-opened
	rocksdb::DB* _db;
	rocksdb::Options* _options;
//	std::shared_ptr<rocksdb::Cache> _cache;
	const rocksdb::Comparator* _comparator;

	// number of open snapshots, associated with RocksDB object
	int n_snapshots;

	// number of open iterators, associated with RocksDB object
	int n_iterators;
} PyRocksDB;

typedef struct {
	PyObject_HEAD

	// the associated RocksDB object
	PyRocksDB* db;

	// the snapshot
	const rocksdb::Snapshot* snapshot;
} PyRocksDBSnapshot;

typedef struct {
	PyObject_HEAD

	// the associated RocksDB object or snapshot
	PyObject* ref;

	// the associated db object
	PyRocksDB* db;

	// the iterator
	rocksdb::Iterator* iterator;

	// upper/lower limit, inclusive, if any
	std::string* bound;

	// iterator direction
	int is_reverse;

	// if 1: return (k, v) 2-tuples, otherwise just k
	int include_value;
} PyRocksDBIter;

typedef struct {
	bool is_put;
	std::string key;
	std::string value;
} PyWriteBatchEntry;

typedef struct {
	PyObject_HEAD
	std::vector<PyWriteBatchEntry>* ops;
} PyWriteBatch;

// custom types
extern PyTypeObject PyRocksDB_Type;
extern PyTypeObject PyRocksDBSnapshot_Type;
extern PyTypeObject PyWriteBatch_Type;
extern PyTypeObject PyRocksDBIter_Type;

#define PyRocksDB_Check(op) PyObject_TypeCheck(op, &PyRocksDB_Type)
#define PyRocksDBSnapshotCheck(op) PyObject_TypeCheck(op, &PyRocksDBSnapshot_Type)
#define PyWriteBatch_Check(op) PyObject_TypeCheck(op, &PyWriteBatch_Type)

extern PyObject* rocksdb_exception;

extern const char pyrocksdb_repair_db_doc[];
extern const char pyrocksdb_destroy_db_doc[];

extern PyObject* pyrocksdb_repair_db(PyRocksDB* self, PyObject* args, PyObject* kwds);
extern PyObject* pyrocksdb_destroy_db(PyObject* self, PyObject* args);

#endif
