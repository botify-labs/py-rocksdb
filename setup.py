#!/usr/bin/python

# Copyright (c) Arni Mar Jonsson.
# See LICENSE for details.

import sys

try:
	from setuptools import setup, Extension
except ImportError:
	from distutils.core import setup, Extension

extra_compile_args = ['-std=c++11', '-I/usr/local/include', '-fPIC', '-Wall', '-g2',
					  '-D_GNU_SOURCE', '-O2', '-DNDEBUG', '-fno-strict-aliasing']
extra_link_args = ['-L/usr/local/lib', '-Bstatic', '-lrocksdb', '-Bstatic', '-lsnappy']

setup(
	name = 'rocksdb',
	version = '0.1',
	# maintainer = 'Arni Mar Jonsson',
	# maintainer_email = 'arnimarj@gmail.com',
	# url = 'http://code.google.com/p/py-rocksdb/',

	classifiers = [
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

	description = 'Python bindings for rocksdb database library',

	packages = ['rocksdb'],
	package_dir = {'rocksdb': ''},

	ext_modules = [
		Extension('rocksdb',
			sources = [
				# python stuff
				'rocksdb_ext.cc',
				'rocksdb_object.cc',
			],
			libraries = ['stdc++'],

			extra_compile_args = extra_compile_args,
			extra_link_args = extra_link_args
		)
	]
)
