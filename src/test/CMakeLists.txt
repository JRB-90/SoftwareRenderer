cmake_minimum_required (VERSION 3.8)

link_directories(test
	C:\\SDL2\\lib\\x64
)

add_executable(test
	Main.cpp
)

target_link_libraries(test PUBLIC
	SDL2
)

target_include_directories(test PUBLIC
	C:\\SDL2\\include
)