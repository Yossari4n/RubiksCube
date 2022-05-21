cmake_minimum_required(VERSION 2.8.12)
project(RubiksCube)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")

add_subdirectory(src)
target_compile_definitions(RubiksCube PRIVATE CONFIGURATION="$(ConfigurationName)")