cmake_minimum_required(VERSION 3.10)
project(ysim)
add_executable(ysim main.cpp)

add_subdirectory(./yassembler yassembler)
add_subdirectory(./mem mem)
add_subdirectory(./proc proc)
add_subdirectory(./global global)
target_link_libraries(ysim PUBLIC yassembler)
target_link_libraries(ysim PUBLIC mem)
target_link_libraries(ysim PUBLIC proc)
target_link_libraries(ysim PUBLIC global)
target_include_directories(ysim PUBLIC
                           "./build"
                           "./yassembler")  
target_include_directories(ysim PUBLIC
                           "./build"
                           "../mem")                       
target_include_directories(ysim PUBLIC
                           "./build"
                           "../proc")   
target_include_directories(ysim PUBLIC
                           "./build"
                           "../global")   
