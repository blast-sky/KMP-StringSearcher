cmake_minimum_required(VERSION 3.5)
project(AAC_lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

FILE(GLOB SRC_HPP "src/*.hpp")

add_executable(${PROJECT_NAME} "src/main.cpp" ${SRC_HPP})