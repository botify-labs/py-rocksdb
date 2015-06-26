#!/bin/sh
exit 1

set -e;

(
	svn checkout http://snappy.googlecode.com/svn/trunk/ snappy-read-only;
	cd snappy-read-only;
	./autogen.sh;
	./configure --enable-shared=no --enable-static=yes;
	make clean;
	make CXXFLAGS='-g -O2 -fPIC';
)

(
	git clone https://code.google.com/p/rocksdb/ || (cd rocksdb; git pull);
	cd rocksdb;
	make clean;
	make librocksdb.a LDFLAGS='-L../snappy-read-only/.libs/ -Bstatic -lsnappy' OPT='-fPIC -O2 -DNDEBUG -DSNAPPY -I../snappy-read-only' SNAPPY_CFLAGS=''
)
