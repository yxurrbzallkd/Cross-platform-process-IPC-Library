cmake_minimum_required(VERSION 3.6)
set(PROJECT_NAME hello)
project(Hello CXX)
set(CMAKE_CXX_STANDARD 11)
message("======================\n" "Host system is:" ${CMAKE_HOST_SYSTEM_NAME} "\n======================\n")

add_executable(${PROJECT_NAME} hello.cpp)

if(WIN32)
	message("Windows Here!")
	set(CMAKE_CXX_COMPILER_ID GNU)
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "hello_windows")
elseif (UNIX AND NOT APPLE)
	if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
		message("Linux Here!")
		set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "hello_linux")
	endif()
	if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Minix")
		message("Minix Here!")
		set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "hello_minix")
	endif()
else()
	message(FATAL_ERROR ${CMAKE_HOST_SYSTEM_NAME} "not supported")
endif()


