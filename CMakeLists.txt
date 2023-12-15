cmake_minimum_required(VERSION 3.10)
project(yassembler)
add_executable(yassembler main.cpp)

add_subdirectory(include)
target_link_libraries(yassembler PUBLIC include)
target_include_directories(yassembler PUBLIC
                           "./build"
                           "./include")                       