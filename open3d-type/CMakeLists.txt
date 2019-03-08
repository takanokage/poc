cmake_minimum_required(VERSION 3.0.0)

set (CMAKE_CXX_STANDARD 11)

# add source files
file(GLOB_RECURSE ALL_SOURCE_FILES "*.cpp")
file(GLOB_RECURSE ALL_HEADER_FILES "*.h")

list(REMOVE_ITEM ALL_SOURCE_FILES matrix.cpp)
list(REMOVE_ITEM ALL_HEADER_FILES matrix.h)

# use the root folder as the project name
get_filename_component(ProjectName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ProjectName})

# create target executable
add_executable(${CMAKE_PROJECT_NAME}
    ${ALL_HEADER_FILES}
    ${ALL_SOURCE_FILES})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
