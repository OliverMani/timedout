cmake_minimum_required(VERSION 3.5.0)
project(timedout VERSION 0.1.0 LANGUAGES C)

file(GLOB SOURCES src/*.c)
include_directories(include/)

add_executable(timedout ${SOURCES})

install(TARGETS timedout RUNTIME DESTINATION bin)