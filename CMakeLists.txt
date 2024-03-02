cmake_minimum_required( VERSION 3.5 )

project( ngrm VERSION 0.1 LANGUAGES CXX )
set(PROJECT_DESCRIPTION "3D Engine framework in C++")

include(GNUInstallDirs)

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
endif()

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
add_compile_options(-std=gnu++26 -march=native -mfpmath=sse+387 -mveclibabi=svml -O3)
add_compile_options(-DGLCOREARB=1)
add_compile_options(-DGLFW=1)
add_compile_options(-D_FILE_OFFSET_BITS=64)
add_compile_options(-fdata-sections)
add_compile_options(-fpermissive)
add_compile_options(-ffunction-sections)
add_compile_options(-Wall)
add_compile_options(-Wno-format-contains-nul)
#add_compile_options(-Wextra)
add_compile_options(-Wpedantic)
add_link_options(-Wl,--gc-sections)
#add_link_options(-Wl,--print-gc-sections)
add_link_options(-Wl,-s)

find_package(OpenGL)
find_package(glfw3)

add_executable( ${PROJECT_NAME} src/main.cpp ) 
target_include_directories( ${PROJECT_NAME} PUBLIC GLFW::GFLW
	PUBLIC_HEADER $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries( ${PROJECT_NAME} glfw3 OpenGL OpenGL::GLU)

