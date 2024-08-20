cmake_minimum_required(VERSION 3.30.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(clichatapp)

if (UNIX AND NOT APPLE)
   find_library(ENET libenet.a REQUIRED)
endif (UNIX AND NOT APPLE)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

if (UNIX AND NOT APPLE)
   target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif (UNIX AND NOT APPLE)

if (WIN32)
   target_include_directories(${PROJECT_NAME} PUBLIC include C:/msys64/ucrt64/include)
   target_link_directories(${PROJECT_NAME} PUBLIC C:/msys64/ucrt64/lib)
endif (WIN32)

target_link_libraries(${PROJECT_NAME} PUBLIC ncursesw enet)
