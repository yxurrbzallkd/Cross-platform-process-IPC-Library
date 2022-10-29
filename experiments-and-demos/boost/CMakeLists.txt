cmake_minimum_required(VERSION 3.15)

#! Check every comment after the "#!"

#! CHANGE YOUR PROJECT NAME
set(PROJECT_NAME main)
project(${PROJECT_NAME} C CXX) # project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_CXX_STANDARD 17)

#! Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

#! Build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

#! Project source compilation
add_executable(${PROJECT_NAME} src/main.cpp)

#! Add external packages
find_package(Boost 1.71.0 COMPONENTS thread program_options regex filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} Boost::thread) # not explicitly used in my program, but required by Boost.process and Boost.Interprocess
target_link_libraries(${PROJECT_NAME} Boost::program_options)
target_link_libraries(${PROJECT_NAME} Boost::regex)
target_link_libraries(${PROJECT_NAME} Boost::filesystem)
#! set output directory (bin)
set_target_properties(${PROJECT_NAME}
						PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)

#####################################
# Define ALL_TARGETS variable to use in PVS and Sanitizers
set (ALL_TARGETS ${PROJECT_NAME})

# Include fixed CMake configuration


