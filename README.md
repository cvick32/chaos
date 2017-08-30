## BUILD

cd chaos &&

mkdir build &&

cd build &&
 
cmake -DCMAKE_BUILD_TYPE=Debug .. &&

make

./stream_test - encrypts a 22 byte msg
