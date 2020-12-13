cmake_minimum_required (VERSION 3.8)

project (Engine2D)

find_library(math NAMES math)
find_library(engine NAMES engine)

link_directories(test
	C:\\SDL2\\lib\\x64
	C:\\SDL2_image\\lib\\x64
)

add_library(engine2d STATIC
	RenderingEngine2D.cpp
	RenderingEngine2D.h
	Point2D.cpp
	Point2D.h
	Line2D.cpp
	Line2D.h
	Scene2D.cpp
	Scene2D.h
    Polygon2D.h
	Polygon2D.cpp
	
	
    Utils2D.h 
	Utils2D.cpp
    Sprite2D.h
	Sprite2D.cpp
	Primitive2DRenderer.h
	Primitive2DRenderer.cpp
    Vertex2D.h
    VBO2D.h
	VBO2D.cpp
)

target_link_libraries(engine2d PUBLIC
	SDL2
	SDL2_image
	math
	engine
)

target_include_directories(engine2d PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	C:\\SDL2\\include
	C:\\SDL2_image\\include
)