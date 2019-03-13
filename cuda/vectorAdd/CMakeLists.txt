cmake_minimum_required(VERSION 3.9)

# use the root folder as the project name
get_filename_component(ProjectName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ProjectName} LANGUAGES CXX CUDA)

list(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_61,code=sm_61)

# set(CMAKE_VERBOSE_MAKEFILE ON)

message(STATUS "Using installed CUDA ${CUDA_VERSION}")

# create target executable
add_executable(${CMAKE_PROJECT_NAME} vectorAdd.cu main.cu)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
