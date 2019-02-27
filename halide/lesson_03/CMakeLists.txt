cmake_minimum_required(VERSION 3.0.0)

# add source files
file(GLOB_RECURSE ALL_SOURCE_FILES "*.cpp")
file(GLOB_RECURSE ALL_HEADER_FILES "*.h")

set(HALIDE_SOURCE_DIR "~/halide")
include_directories(${HALIDE_SOURCE_DIR}/include)
link_directories(${HALIDE_SOURCE_DIR}/bin)
link_libraries(Halide)

# use the root folder as the project name
get_filename_component(ProjectName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ProjectName})

# create target executable
add_executable(${CMAKE_PROJECT_NAME} ${ALL_HEADER_FILES} ${ALL_SOURCE_FILES})

# Set OS-specific things here
if (WIN32)
elseif (CYGWIN)
elseif (APPLE)
elseif (UNIX)
    add_definitions(-DUNIX)

    # enable c++11
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wno-unused-result)

    add_definitions(-O3)
endif ()

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
