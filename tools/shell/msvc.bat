@ECHO OFF

pushd "%PRP%\build"

rem CALL "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

rem cmake .. -DCMAKE_C_COMPILER="cl.exe" -DCMAKE_CXX_COMPILER="cl.exe" -DNO_CXX_COMPILER=FALSE
rem cmake -G "Visual Studio 17 2022" -A x64 ..

rem IF EXIST CMakeCache.txt DEL /F /Q CMakeCache.txt
rem IF EXIST CMakeFiles rmdir /S /Q CMakeFiles
rem IF EXIST build.ninja DEL /F /Q build.ninja

cmake .. -DCMAKE_C_COMPILER="cl.exe" -DCMAKE_CXX_COMPILER="cl.exe"

popd