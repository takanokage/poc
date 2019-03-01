#!/bin/bash

. clean.sh

echo generating...

mkdir -p build
cd build

cmake .. -DCMAKE_BUILD_TYPE=RELEASE

echo
echo building...

make -j $(nproc)

echo
