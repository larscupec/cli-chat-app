cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(clichatapp LANGUAGES CXX)

if (UNIX AND NOT APPLE)
   find_library(ENET libenet.a REQUIRED)
endif (UNIX AND NOT APPLE)

if (WIN32)
   set(ENET_INCLUDE_DIR C:/msys64/ucrt64/include)
endif (WIN32)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(clichatapp ${SRC_FILES})

if (UNIX AND NOT APPLE)
   target_include_directories(clichatapp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif (UNIX AND NOT APPLE)

if (WIN32)
   target_include_directories(clichatapp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${ENET_INCLUDE_DIR})
endif (WIN32)

target_link_libraries(clichatapp PUBLIC -lenet)
