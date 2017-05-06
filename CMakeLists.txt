cmake_minimum_required(VERSION 3.6)

project(Address-Book)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c dbg.h fileoperations.c fileoperations.h records.c records.h indexing.c)

add_executable(contacts ${SOURCE_FILES})