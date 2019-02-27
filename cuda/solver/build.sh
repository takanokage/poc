#!/bin/bash

. clean.sh

echo generating...

mkdir -p build
cd build

cmake ..

echo
echo building...

make -j $(nproc)

echo
