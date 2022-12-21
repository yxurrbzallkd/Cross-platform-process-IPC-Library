cmake_minimum_required(VERSION 3.15)

#! Check every comment after the "#!"

#! CHANGE YOUR PROJECT NAME
set(PROJECT_NAME test)
project(${PROJECT_NAME} C CXX) # project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_CXX_STANDARD 17)

#! Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

#! Build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

#! Add external packages
find_package(Boost 1.71.0 COMPONENTS thread program_options regex filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Boost::thread is not explicitly used in my program, but required by Boost.process and Boost.Interprocess
set(libs Boost::thread Boost::program_options Boost::regex Boost::filesystem)

#! Project source compilation
set(targets shmem fmap_shmem shmem_managed)
foreach(target ${targets})
	add_executable(${target}_test src/${target}_test.cpp)
	target_link_libraries(${target}_test ${libs})
	set_target_properties(${target}_test
						PROPERTIES
						RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)

endforeach(target ${targets})
