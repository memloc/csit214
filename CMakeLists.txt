cmake_minimum_required(VERSION 3.16)
project(simple)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# source directories
set(HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# project source files
set(SOURCES 
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/Lexer.cpp"
	"${SOURCE_DIR}/Parser.cpp"
	"${SOURCE_DIR}/Compiler.cpp"
)

set(HEADERS
	"${HEADER_DIR}/Token.h"
	"${HEADER_DIR}/Lexer.h"
	"${HEADER_DIR}/Parser.h"
	"${HEADER_DIR}/Bytecode.h"
	"${HEADER_DIR}/Compiler.h"
	"${HEADER_DIR}/VirtualMachine.h"
)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${HEADER_DIR}>
	$<INSTALL_INTERFACE:${HEADER_DIR}>
)
