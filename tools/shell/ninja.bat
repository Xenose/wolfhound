@ECHO OFF

pushd "%PRP%\build"

IF EXIST CMakeCache.txt DEL /F /Q CMakeCache.txt
IF EXIST CMakeFiles rmdir /S /Q CMakeFiles
IF EXIST build.ninja DEL /F /Q build.ninja

cmake .. -G "Ninja"

popd
