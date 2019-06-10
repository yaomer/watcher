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
CXXFLAGS="-std=c++11 -o wcr"
SRC="*.cc"

echo "$CXX $CXXFLAGS $SRC"
$CXX $CXXFLAGS $SRC
