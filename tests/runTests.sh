#!/usr/bin/env bash

# go to this scripts directory
cd "$(dirname "$0")"

# clean build dir
if [ -d "build" ]; then
  rm -rf build
fi
mkdir build

# build project
cd build
cmake ../..
make
cp clone-finder/clang-clone-finder .
cp fakecc/clang-clone-finder-fakecc .
cd ..

cd testproject1

../build/clang-clone-finder make