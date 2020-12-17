cmake_minimum_required (VERSION 3.8)

project (Engine3D)

find_library(math NAMES math)
find_library(engine NAMES engine)

link_directories(test
	C:\\SDL2\\lib\\x64
)

add_library(engine3d STATIC
	RenderingEngine3D.cpp
	RenderingEngine3D.h
    Scene3D.h
	Scene3D.cpp
	Camera.h
	Camera.cpp
)

target_link_libraries(engine3d PUBLIC
	SDL2
	math
	engine
)

target_include_directories(engine3d PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	C:\\SDL2\\include
)