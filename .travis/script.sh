if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    make CC=${CC} CXX=${CXX} all && make CC=${CC} CXX=${CXX} test && ./coverage.sh gcov-4.9
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    make CC=${CC} CXX=${CXX} all && make CC=${CC} CXX=${CXX} test
fi

