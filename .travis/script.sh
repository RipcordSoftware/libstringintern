mkdir -p .travis.temp
pushd .travis.temp

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    export CC=gcc-4.9
    export CXX=g++-4.9
    make all && make test && ./coverage.sh gcov-4.9
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    export CC=clang
    export CXX=clang++
    make all && make test
fi

popd
