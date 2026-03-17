@ECHO OFF

pushd "%PRP%\build"

cmake --build "%PRP%\build"

popd
