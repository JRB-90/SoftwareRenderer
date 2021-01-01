cmake_minimum_required (VERSION 3.8)

project (Model_importer)

find_library(engine NAMES engine)
find_library(engine3d NAMES engine3d)

link_directories(model_importer
	C:\\Assimp\\lib\\x64
	C:\\Development\\Other\\assimp\\assimp\\lib\\Release
)

add_library(model_importer STATIC
	ModelImporter.h
	ModelImporter.cpp
    StlLoader.h
	StlLoader.cpp
    FileUtils.h
	FileUtils.cpp
    AssimpImporter.h
	AssimpImporter.cpp
)

target_link_libraries(model_importer PUBLIC
	engine
	engine3d
)

target_include_directories(model_importer PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	C:\\Assimp\\include
)