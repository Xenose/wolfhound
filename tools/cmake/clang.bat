@ECHO OFF

cd "%PRP%\build"
cmake .. -DCMAKE_C_COMPILER=/usr/bin/clang
cd "%PRP%"
