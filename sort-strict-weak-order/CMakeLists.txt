cmake_minimum_required(VERSION 3.15)
project(sort_strict_weak_order)

set(BIN_NAME sort_strict_weak_order)
set(CMAKE_CXX_STANDARD 17)

add_executable(${BIN_NAME} main.cc)

if(WIN32)
	target_compile_options(${BIN_NAME} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
endif()