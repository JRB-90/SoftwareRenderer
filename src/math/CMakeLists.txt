cmake_minimum_required (VERSION 3.8)

project (Math)

add_library(math STATIC
	Vector2D.cpp
	Vector2D.h
    Vector3D.h
	Vector3D.cpp
    Frame2D.h 
	Frame2D.cpp
	MathUtils.h
	MathUtils.cpp
)

target_include_directories(math PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)