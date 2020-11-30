cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("SoftwareRenderer")

add_subdirectory("src/math")
add_subdirectory("src/engine")
add_subdirectory("src/engine2d")

add_subdirectory("src/sdl_test")
add_subdirectory("src/engine_test")
add_subdirectory("src/starfield")
