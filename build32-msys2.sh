rm -rf build32
mkdir build32
cd build32
cmake .. -G"MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/mingw64/x86_64-w64-mingw32
make