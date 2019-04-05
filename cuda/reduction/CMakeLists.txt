cmake_minimum_required(VERSION 3.9)

file(GLOB_RECURSE ALL_SOURCE_FILES "*.cpp")
file(GLOB_RECURSE ALL_HEADER_FILES "*.h")
file(GLOB_RECURSE CUDA_SOURCE_FILES "*.cu")
file(GLOB_RECURSE CUDA_HEADER_FILES "*.cuh")

# use the root folder as the project name
get_filename_component(ProjectName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ProjectName} LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_VERBOSE_MAKEFILE ON)

message(STATUS "Using installed CUDA ${CUDA_VERSION}")

# create target executable
add_executable(${CMAKE_PROJECT_NAME} ${ALL_SOURCE_FILES} ${ALL_HEADER_FILES} ${CUDA_SOURCE_FILES} ${CUDA_HEADER_FILES})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# set include directories
include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
