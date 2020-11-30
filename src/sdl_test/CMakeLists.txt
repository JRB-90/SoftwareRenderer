cmake_minimum_required (VERSION 3.8)

link_directories(sdl_test
	C:\\SDL2\\lib\\x64
)

add_executable(sdl_test
	Main.cpp
)

target_link_libraries(sdl_test PUBLIC
	SDL2
)

target_include_directories(sdl_test PUBLIC
	C:\\SDL2\\include
)