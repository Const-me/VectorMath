cmake_minimum_required(VERSION 2.8.12)
project(VectorMath)
include_directories("Include")
set(CMAKE_SUPPRESS_REGENERATION true)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options( "-std=c++1z" )
	add_compile_options( "-stdlib=libc++" )
	add_compile_options( "-O3" )
	add_compile_options( "-march=native" )
endif()

source_group( "Main" FILES "VectorMath.cpp" )

FILE( GLOB CVM_INC LIST_DIRECTORIES false "Include/*" )
FILE( GLOB CVM_INC_IMPL LIST_DIRECTORIES false "Include/impl/*.*" )

source_group( "Include" FILES ${CVM_INC})
source_group( "Include\\impl" FILES ${CVM_INC_IMPL})

add_executable (
	VectorMath
	VectorMath.cpp
	${CVM_INC}
	${CVM_INC_IMPL}
)