mkdir -p .travis.temp
pushd .travis.temp

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    curl http://ftp.uk.debian.org/debian/pool/main/l/lcov/lcov_1.11.orig.tar.gz -O
    tar xfz lcov_1.11.orig.tar.gz
    mkdir -p lcov && make -C lcov-1.11/ install PREFIX=~/lcov
    export PATH=~/lcov/usr/bin:$PATH

    gem install coveralls-lcov
    pip install --user json_tools u-msgpack-python
    export PATH=~/.local/bin:$PATH
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    brew update
    brew install make
fi

popd
