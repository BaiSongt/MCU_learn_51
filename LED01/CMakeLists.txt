project(LED)
cmake_minimum_required(VERSION 3.10)

message("CMAKE_PROJECT_DIR = " ${CMAKE_PROJECT_DIR})

add_library(STC89XX ${CMAKE_PROJECT_DIR}/lib)
target_include_directories(STC89XX PUBLIC ${CMAKE_PROJECT_DIR}/lib)

add_executable(main ${CMAKE_PROJECT_DIR}/src/main.c)
target_link_libraries(main STC89XX)