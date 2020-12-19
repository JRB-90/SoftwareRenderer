cmake_minimum_required (VERSION 3.8)

project (Engine3D)

find_library(math NAMES math)
find_library(engine NAMES engine)
find_library(engine2d NAMES engine2d)

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
    Mesh3D.h
	Mech3D.cpp
    VBO3D.h
	VBO3D.cpp
    Vertex3D.h
    Primitive3DRenderer.h
	Primitive3DRenderer.cpp
    MeshBuilder.h
	MeshBuilder.cpp
)

target_link_libraries(engine3d PUBLIC
	SDL2
	math
	engine
	engine2d
)

target_include_directories(engine3d PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	C:\\SDL2\\include
)