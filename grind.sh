#!/bin/bash

CONF=Debug
if [ "$1" != "" ]; then
	CONF=$1
fi

make CONF=${CONF} && make CONF=${CONF} test

for f in src/libstringintern/build/${CONF}/GNU-Linux-x86/tests/TestFiles/*; do
	valgrind $f --gtest_repeat=10
done

pushd src/testlibstringintern
valgrind dist/${CONF}/GNU-Linux-x86/testlibstringintern 
valgrind --tool=cachegrind dist/${CONF}/GNU-Linux-x86/testlibstringintern 
popd

