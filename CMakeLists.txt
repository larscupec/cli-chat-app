cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(clichatapp)

find_library(ENET libenet.a REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(clichatapp ${SRC_FILES})
target_include_directories(clichatapp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(clichatapp PUBLIC ${ENET})
