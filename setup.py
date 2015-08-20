#!/usr/bin/python

# Adapted from py-leveldb, which is
# Copyright (c) Arni Mar Jonsson.
# See LICENSE for details.

import sys

VERSION = '3.13.0.2'

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

extra_compile_args = [
    '-DVERSION="' + VERSION + '"',
    '-std=c++11',
    # '-I/usr/local/include',
    '-fPIC',
    '-Wall',
    '-g2',
    '-D_GNU_SOURCE',
    '-O2', '-DNDEBUG', '-fno-strict-aliasing'
]
extra_link_args = [
    '-L.',
    '-lrocksdb', '-lsnappy', '-llz4', '-lz', '-lbz2'
]

setup(
    name='rocksdb',
    version=VERSION,
    maintainer='zeb',
    maintainer_email='zeb@botify.com',
    url = 'https://github.com/botify-labs/py-rocksdb/',
    license='BSD',

    classifiers=[
        'Development Status :: 4 - Beta',
        'Environment :: Other Environment',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: BSD License',
        'Operating System :: POSIX',
        'Programming Language :: C++',
        'Programming Language :: Python',
        'Programming Language :: Python :: 2.4',
        'Programming Language :: Python :: 2.5',
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.0',
        'Programming Language :: Python :: 3.1',
        'Programming Language :: Python :: 3.2',
        'Programming Language :: Python :: 3.3',
        'Topic :: Database',
        'Topic :: Software Development :: Libraries'
    ],

    description='Python bindings for the RocksDB database library',

    packages=['rocksdb'],
    package_dir={'rocksdb': ''},

    ext_modules=[
        Extension('rocksdb',
                  sources=[
                      # python stuff
                      'rocksdb_ext.cc',
                      'rocksdb_object.cc',
                  ],
                  libraries=['stdc++'],

                  extra_compile_args=extra_compile_args,
                  extra_link_args=extra_link_args
                  )
    ]
)
