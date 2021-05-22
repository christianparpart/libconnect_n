cmake_minimum_required(VERSION 3.10)

project(connect_n VERSION "0.0.1" LANGUAGES CXX)

# Let's stick to modern C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# usualy provided by outside CLI command, required by LSP plugins
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(ClangTidy)
include(ThirdParties)
ThirdPartiesAdd_Catch2()
ThirdPartiesAdd_fmtlib()
ThirdPartiesAdd_range_v3()

if(("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU") OR ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang"))
    add_compile_options(-Wall)
    add_compile_options(-Wextra)
elseif(DEFINED MSVC)
    add_definitions(-DNOMINMAX)
    add_definitions(-D_USE_MATH_DEFINES)
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(connect_n)
