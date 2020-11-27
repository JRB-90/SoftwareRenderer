cmake_minimum_required (VERSION 3.8)

project (Engine)

find_library(math NAMES math)

add_library(engine STATIC
    Input.cpp
	Input.h
	Color.cpp
	Color.h
	RenderingMode.h
)

target_link_libraries(engine PUBLIC
	SDL2
	math
)

target_include_directories(engine PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	C:\\SDL2\\include
)