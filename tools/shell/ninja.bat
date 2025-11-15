@ECHO OFF

pushd "%PRP%\build"

rem IF EXIST CMakeCache.txt DEL /F /Q CMakeCache.txt
rem IF EXIST CMakeFiles rmdir /S /Q CMakeFiles
rem IF EXIST build.ninja DEL /F /Q build.ninja

cmake .. -G "Ninja"

popd
