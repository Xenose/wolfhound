@ECHO OFF

pushd "%PRP%\build"

rem cmake .. -DCMAKE_C_COMPILER="cl.exe" -DCMAKE_CXX_COMPILER="cl.exe" -DNO_CXX_COMPILER=FALSE

cd build

rmdir /S /Q CMakeFiles
del /Q CMakeCache.txt
del /Q build.ninja

cmake -G "Visual Studio 17 2022" -A x64 ..

popd