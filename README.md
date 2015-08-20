py-rocksdb: Python bindings for RocksDB 
Adapted from py-leveldb, which author is Arni Mar Jonsson (arnimarj@gmail.com)

This is mostly py-leveldb with references to LevelDB replaced. With a notable difference:
a `RocksDB.Close` method. May not be safe when multithreading.

The constructor also have some differences:
* removed: block_size, block_restart_interval, block_cache_size
* added: prepare_for_bulk_load, read_only, compression_type
* also added, less useful?: disable_data_sync, use_adaptive_mutex


Note: an easy way to crash the library is closing a db with open iterators.




# Build Instructions

Build rocksdb:

```
cd rocksdb
PORTABLE=1 make static_lib EXTRA_CXXFLAGS=-fPIC EXTRA_LDFLAGS=-fPIC
fakeroot make install # Or copy librocksdb.a into py-rocksdb directory; include/ too
```

Then, the extension itself:

python setup.py build

Then `setup.py install` or `setup.py develop` to deploy in your virtualenv.

# Example Usage


```python
>>> import rocksdb
>>> db = rocksdb.RocksDB('./db')
>>> db.Put('hello', 'world')
>>> print db.Get('hello')
world
>>> db.Delete('hello')
>>> db.Get('hello')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
KeyError
>>> for i in xrange(10):
...   db.Put(str(i), 'string_%s' % i)
...
>>> print list(db.RangeIter(key_from = '2', key_to = '5'))
[('2', 'string_2'), ('3', 'string_3'), ('4', 'string_4'), ('5', 'string_5')]
>>> batch = rocksdb.WriteBatch()
>>> for i in xrange(1000):
...   db.Put(str(i), 'string_%s' % i)
...
>>> db.Write(batch, sync = True)
>>>
```