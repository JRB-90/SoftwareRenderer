cmake_minimum_required (VERSION 3.8)

find_library(engine NAMES engine)
find_library(engine2d NAMES engine2d)

link_directories(test
	C:\\SDL2\\lib\\x64
	C:\\SDL2_image\\lib\\x64
	C:\\SDL2_ttf\\lib\\x64
)

add_executable(engine2d_test
	Main.cpp
)

target_link_libraries(engine2d_test PUBLIC
	engine
	engine2d
)

target_include_directories(engine2d_test PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)