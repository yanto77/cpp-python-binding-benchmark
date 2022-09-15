BUILD_DIR="./build"

rm -rf $BUILD_DIR
cmake -S. -B$BUILD_DIR -DCMAKE_BUILD_TYPE:STRING=Release
cmake --build $BUILD_DIR --config Release -j 
