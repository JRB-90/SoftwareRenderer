cmake_minimum_required (VERSION 3.8)

find_library(engine NAMES engine)
find_library(engine2d NAMES engine2d)

link_directories(test
	C:\\SDL2\\lib\\x64
)

add_executable(engine_test
	Main.cpp
)

target_link_libraries(engine_test PUBLIC
	engine
	engine2d
)

target_include_directories(engine_test PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)