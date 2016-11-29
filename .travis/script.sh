make CC=${_CC} CXX=${_CXX} all && make CC=${_CC} CXX=${_CXX} test || exit $?

if [ "${_COV}" != "" ]; then
    ./coverage.sh ${_COV}
fi
