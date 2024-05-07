cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(PECS)

add_subdirectory(Basis)
add_subdirectory(Database)
add_subdirectory(Executables)