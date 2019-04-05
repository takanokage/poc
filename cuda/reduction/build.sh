#!/bin/bash

. clean.sh

echo generating...

mkdir -p build
cd build

~/cmake/v3.13.4/bin/cmake ..

echo
echo building...

make -j $(nproc)

echo
