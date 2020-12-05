cmake_minimum_required (VERSION 3.8)

project (Engine)

find_library(math NAMES math)

link_directories(test
	C:\\SDL2\\lib\\x64
	C:\\SDL2_image\\lib\\x64
)

add_library(engine STATIC
	Color.cpp
	Color.h
	RenderingMode.h
    RenderingWindow.cpp
    RenderingWindow.h
	Engine.cpp
    Engine.h
	IRenderingEngine.h
	IScene.h
	ImageLoader.cpp
    ImageLoader.h
	Texture.cpp
	Texture.h
    ResourceManager.cpp
	ResourceManager.h
    IResource.h
)

target_link_libraries(engine PUBLIC
	SDL2
	SDL2_image
	math
)

target_include_directories(engine PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	C:\\SDL2\\include
	C:\\SDL2_image\\include
)