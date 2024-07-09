cmake_minimum_required(VERSION 3.5)
project(TTFY)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(TTFY_SRC src/TTFY_buffer.c src/TTFY_TableDirectory.c
    src/TTFY_head.c src/TTFY_hhea.c src/TTFY_maxp.c
    src/TTFY_htmx.c)
if(WIN32)
    add_definitions(-DTTFY_BUILD -DTTFY_DLL)
endif(WIN32)
add_library(${PROJECT_NAME} SHARED ${TTFY_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include/)

