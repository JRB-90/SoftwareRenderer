cmake_minimum_required (VERSION 3.8)

link_directories(engine3d_test
	C:\\freeglut\\lib\\x64
)

add_executable(glut_test
	Main.cpp
)

target_link_libraries(glut_test PUBLIC
	freeglut
	OpenGL32
)

target_include_directories(glut_test PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	C:\\freeglut\\include
)
