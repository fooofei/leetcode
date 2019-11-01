
cmake_minimum_required(VERSION 3.1)
project(leetcode-windows)

if(APPLE)
    set(CMAKE_MACOSX_RPATH 0)
endif()

set(CMAKE_CXX_STANDARD 17)
set(BIN_NAME test1)


if(WIN32)
else()
endif()

set(Source_files 
    ${CMAKE_CURRENT_LIST_DIR}/manacher.cc
	)

add_executable(${BIN_NAME} ${Source_files})


source_group(files FILES ${Source_files})

if(WIN32)
	target_compile_options(${BIN_NAME} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
	target_compile_definitions(${BIN_NAME} PRIVATE WIN32)
else()
    
endif()
