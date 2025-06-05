@ECHO OFF

pushd "%PRP%\build"

IF EXIST CMakeCache.txt DEL /f /q CMakeCache.txt
cmake .. -G "Ninja"

popd
