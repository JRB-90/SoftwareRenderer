cmake_minimum_required (VERSION 3.8)

project (Engine)

find_library(math NAMES math)

link_directories(test
	C:\\SDL2\\lib\\x64
)

add_library(engine STATIC
	Color.cpp
	Color.h
	RenderingMode.h
    RenderingWindow.h
    RenderingWindow.cpp
    Engine.h
	Engine.cpp
	IRenderingEngine.h
	IScene.h
)

target_link_libraries(engine PUBLIC
	SDL2
	math
)

target_include_directories(engine PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	C:\\SDL2\\include
)