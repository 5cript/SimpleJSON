rm -rf build
mkdir build
cd build
cmake .. -G"MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/mingw64/x86_64-w64-mingw64
make