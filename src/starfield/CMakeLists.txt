cmake_minimum_required (VERSION 3.8)

find_library(engine NAMES engine)
find_library(engine2d NAMES engine2d)

link_directories(test
	C:\\SDL2\\lib\\x64
)

add_executable(starfield
	Main.cpp
	Star.cpp
    Star.h
)

target_link_libraries(starfield PUBLIC
	engine
	engine2d
)

target_include_directories(starfield PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)