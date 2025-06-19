#!/bin/bash

set -e

BUILD_DIR="build"
MAIN_EXEC="./build/nibbler"
TEST_EXEC="./build/nibbler_tests"

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake ..
cmake --build .