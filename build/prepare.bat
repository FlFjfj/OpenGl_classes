set path=%path%;C:\Program Files\CMake\bin
cmake.exe .. -A x64 -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_TOOLCHAIN_FILE=C:\Users\youto\Documents\dev\vcpkg\scripts\buildsystems\vcpkg.cmake -G "Visual Studio 15 2017" 
