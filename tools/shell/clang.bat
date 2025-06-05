@ECHO OFF

pushd "%PRP%\build"

cmake .. -DCMAKE_C_COMPILER=clang

popd
