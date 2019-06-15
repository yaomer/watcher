#!/bin/bash

PLATFORM=$(uname -s)
if [ "$PLATFORM" == "Linux" ]; then
    CXX=g++
elif [ "$PLATFORM" == "Darwin" ]; then
    CXX=clang++
else
    echo "Unknown Platform"
    exit 1
fi

# 这里的python版本没有限制，python2 or python3皆可
# 它只用于在C/C++中嵌入python
Python="python2.7"
CXXFLAGS="-std=c++11 -o wcr"
SRC="*.cc"
INCLUDE="-I /usr/include/$Python"
LIB="-l$Python"

echo "$CXX $CXXFLAGS $SRC $INCLUDE $LIB"
$CXX $CXXFLAGS $SRC $INCLUDE $LIB
