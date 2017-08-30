cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(chaos)
set(MY_DEBUG_OPTIONS "-Wall" "-Werror")
set(MY_RELEASE_OPTIONS "-g" "-march=native")

add_library(chaos
	include/chaos/gen.h
	include/chaos/enc.h
	src/attractor.h
	src/seed.h
        src/attractor.c
        src/seed.c
	src/gen.c
	src/enc.c
)
target_include_directories(chaos PUBLIC include)
target_include_directories(chaos PRIVATE src)
add_executable(stream_test
	test/main.c
)
target_compile_options(stream_test PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
target_compile_options(stream_test PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")
target_link_libraries(stream_test chaos)
