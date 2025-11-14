@ECHO OFF

pushd "%PRP%\build"

rem cmake .. -DCMAKE_C_COMPILER="cl.exe" -DCMAKE_CXX_COMPILER="cl.exe" -DNO_CXX_COMPILER=FALSE

rem cmake -G "Visual Studio 17 2022" -A x64 ..
rem cmake .. -DCMAKE_C_COMPILER="cl.exe" -DCMAKE_CXX_COMPILER="cl.exe"

IF EXIST CMakeCache.txt DEL /F /Q CMakeCache.txt
IF EXIST CMakeFiles rmdir /S /Q CMakeFiles
IF EXIST build.ninja DEL /F /Q build.ninja

cmake -G "Visual Studio 17 2022" -A x64 ..

popd