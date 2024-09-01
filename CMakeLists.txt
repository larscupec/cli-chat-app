cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(clichatapp VERSION 1.0)

configure_file(clichatappConfig.h.in clichatappConfig.h)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include ${PROJECT_BINARY_DIR})

if (WIN32)
   target_include_directories(${PROJECT_NAME} PUBLIC C:/msys64/ucrt64/include)
   target_link_directories(${PROJECT_NAME} PUBLIC C:/msys64/ucrt64/lib)
endif (WIN32)

if (UNIX)
   find_library(ENET enet PATHS $ENV{HOME}/Libs/enet/.libs NO_DEFAULT_PATH)
   find_library(NCURSES ncurses PATHS $ENV{HOME}/Libs/ncurses/lib NO_DEFAULT_PATH)
   target_include_directories(${PROJECT_NAME} PUBLIC $ENV{HOME}/Libs/enet/include $ENV{HOME}/Libs/ncurses/include)
endif (UNIX)

target_link_libraries(${PROJECT_NAME} PUBLIC ${NCURSES} ${ENET} -static-libstdc++)
