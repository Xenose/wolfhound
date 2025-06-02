@ECHO OFF

cd "%PRP%\build"
cmake .. -DCMAKE_C_COMPILER=clang
cd "%PRP%"
