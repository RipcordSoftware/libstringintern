if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    CC=gcc-4.9
    CXX=g++-4.9
    make CC=${CC} CXX=${CXX} all && make CC=${CC} CXX=${CXX} test && ./coverage.sh gcov-4.9
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    CC=clang
    CXX=clang++
    make  CC=${CC} CXX=${CXX} all && make CC=${CC} CXX=${CXX} test
fi

