cmake_minimum_required(VERSION 3.14)
project(max-window)

set(BIN_NAME max_window)
set(CMAKE_CXX_STANDARD 17)

add_executable(${BIN_NAME} main.cc)


if(WIN32)
	target_compile_options(${BIN_NAME} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
endif()