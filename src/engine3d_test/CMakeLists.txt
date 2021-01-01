cmake_minimum_required (VERSION 3.8)

find_library(engine NAMES engine)
find_library(engine3d NAMES engine3d)
find_library(model_importer NAMES model_importer)

link_directories(engine3d_test
	C:\\SDL2\\lib\\x64
	C:\\SDL2_image\\lib\\x64
	C:\\SDL2_ttf\\lib\\x64
	C:\\Development\\Other\\assimp\\assimp\\lib\\Release
)

add_executable(engine3d_test
	Main.cpp
)

target_link_libraries(engine3d_test PUBLIC
	engine
	engine3d
	model_importer
	assimp-vc142-mt
)

target_include_directories(engine3d_test PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)