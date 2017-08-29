cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(chaos)
enable_testing()

add_library(chaos
	include/chaos/gen.h
	src/attractor.h
	src/seed.h
        src/attractor.c
        src/seed.c
	src/gen.c
)
target_include_directories(chaos PUBLIC include)
target_include_directories(chaos PRIVATE src)
add_executable(stream_test
	test/main.c
)
target_link_libraries(stream_test chaos)
