## BUILD

cd chaos &&

mkdir build &&

cd build &&
 
cmake -DCMAKE_BUILD_TYPE=Release .. &&

make

./stream_test - encrypts 100 bytes of 1s

## MISC

state is the current point of the rossler attractor with A=0.4263, B=2, C=4

gen32 returns a mix of each point's mantissa 

156 bits of entropy(?tbd)

callgrind gives 93 IRs for the release build of the gen32 function -> 98 IRs /
4 bytes = 24.5 IRs per byte

stream tested with the testu01 library. multiple runs of BigCrush, Rabbit (100MB
500MB 1GB) FIPS_140_2, have not reported any p values outside accepted ranges 
(so far)
