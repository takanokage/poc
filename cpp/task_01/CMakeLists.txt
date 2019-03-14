cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

# use the root folder as the project name
get_filename_component(ProjectName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ProjectName} LANGUAGES CXX)

# set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB ALL_SOURCE_FILES "*.cpp")
file(GLOB ALL_HEADER_FILES "*.h")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# create target executable
add_executable(${CMAKE_PROJECT_NAME} ${ALL_SOURCE_FILES} ${ALL_HEADER_FILES})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
