make CC=${_CC} CXX=${_CXX} all && make CC=${_CC} CXX=${_CXX} test || exit $?

if [[ "${COV}" != "" ]]; then
    ./coverage.sh ${_COV}
fi
