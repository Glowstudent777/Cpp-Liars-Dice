cmake_minimum_required(VERSION 3.10)
project("LiarsDice")

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")

add_executable(liarsdice ${SOURCES})

target_include_directories(liarsdice PRIVATE ${PROJECT_SOURCE_DIR}/include)

message(STATUS "Created target: liarsdice")