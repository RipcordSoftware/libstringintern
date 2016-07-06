!#/bin/sh
make && make test

for f in src/libstringintern/build/Debug/GNU-Linux-x86/tests/TestFiles/*; do
	valgrind $f --gtest_repeat=10
done

pushd src/testlibstringintern
valgrind dist/Debug/GNU-Linux-x86/testlibstringintern 
valgrind --tool=cachegrind dist/Debug/GNU-Linux-x86/testlibstringintern 
popd

