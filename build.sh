#!/bin/bash

set -e

cd "`dirname "$0"`"

mkdir -p build/

source $(pwd)/env/bin/activate

pushd build/
conan install .. --output-folder . --build missing -s build_type=Debug

if [[ "$OSTYPE" == "darwin"* ]]; then
	cmake .. -G "Xcode"
else
	cmake ..
fi

cmake --build .
popd > /dev/null

deactivate
