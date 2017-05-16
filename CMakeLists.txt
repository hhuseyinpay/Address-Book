cmake_minimum_required(VERSION 3.6)

project(Address-Book)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c dbg.h record.c record.h address_book.c address_book.h )

add_executable(contacts ${SOURCE_FILES})