#Cmake version
cmake_minimum_required(VERSION 3.10)

#project information
project(rsa_threadpool_demo)

aux_source_directory(. DIR_SRCS)

add_subdirectory(include)
add_subdirectory(examples)
add_subdirectory(unit_test)

