cmake_minimum_required(VERSION 3.16)
project(simple)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# source directories
set(HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# project source files
set(SOURCES 
	"${SOURCE_DIR}/main.cpp"
)

set(HEADERS
	"${HEADER_DIR}/Token.h"
)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${HEADER_DIR}>
	$<INSTALL_INTERFACE:${HEADER_DIR}>
)
