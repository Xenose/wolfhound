@ECHO OFF

ECHO PRP IS: %PRP%

cd "%PRP%\build"
IF EXIST CMakeCache.txt DEL /f /q CMakeCache.txt

cmake .. -G "Ninja"
cd "%PRP%"