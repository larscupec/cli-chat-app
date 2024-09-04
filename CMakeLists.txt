cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(clichatapp VERSION 1.0)

configure_file(config.hpp.in config.hpp)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include ${PROJECT_BINARY_DIR})

if (WIN32)
   target_include_directories(${PROJECT_NAME} PUBLIC C:/msys64/ucrt64/include C:/msys64/ucrt64/include/ncurses)
   find_library(ENET enet PATHS C:/msys64/ucrt64/lib NO_DEFAULT_PATH)
   find_library(NCURSES ncursesw PATHS C:/msys64/ucrt64/lib NO_DEFAULT_PATH)
endif (WIN32)

if (UNIX)
   target_include_directories(${PROJECT_NAME} PUBLIC $ENV{HOME}/Libs/enet/include $ENV{HOME}/Libs/ncurses/include)
   find_library(ENET enet PATHS $ENV{HOME}/Libs/enet/.libs NO_DEFAULT_PATH)
   find_library(NCURSES ncurses PATHS $ENV{HOME}/Libs/ncurses/lib NO_DEFAULT_PATH)
endif (UNIX)

target_link_libraries(${PROJECT_NAME} PUBLIC ${NCURSES} ${ENET} -static-libgcc -static-libstdc++)
