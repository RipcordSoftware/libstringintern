mkdir -p .travis.temp
pushd .travis.temp

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    make all CXX=g++-4.9 && make test CXX=g++-4.9 && ./coverage.sh gcov-4.9
fi

popd
