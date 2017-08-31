cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(chaos)

set(MY_DEBUG_OPTIONS "-Wall" "-Werror")
set(MY_RELEASE_OPTIONS "-g")

set(CMAKE_BUILD_TYPE optimized)
set(CMAKE_C_FLAGS_OPTIMIZED "-O3 -march=native")

add_library(chaos
	include/chaos/gen.h
	include/chaos/enc.h
	src/gen.c
	src/enc.c
)
target_include_directories(chaos PUBLIC include)
add_executable(stream_test
	test/main.c
)
target_compile_options(stream_test PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
target_compile_options(stream_test PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")
target_link_libraries(stream_test chaos)
target_link_libraries(stream_test m)
target_link_libraries(stream_test probdist)
target_link_libraries(stream_test mylib)
target_link_libraries(stream_test testu01)
