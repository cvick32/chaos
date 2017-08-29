cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(chaos)

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
add_executable(rng_demo
	test/main.c
)
target_link_libraries(rng_demo chaos)
target_link_libraries(rng_demo m)
target_link_libraries(rng_demo probdist)
target_link_libraries(rng_demo mylib)
target_link_libraries(rng_demo testu01)
