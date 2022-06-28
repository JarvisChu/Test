cmake_minimum_required(VERSION 3.15)

#project(sub)

############ project 项目相关变量 ############

message(STATUS "PROJECT_NAME       : " ${PROJECT_NAME})       # 项目名称，即 project() 中设置，即hello
message(STATUS "PROJECT_SOURCE_DIR : " ${PROJECT_SOURCE_DIR}) # 项目目录
message(STATUS "sub_SOURCE_DIR   : " ${sub_SOURCE_DIR})   # CMAKE 自动生成的变量，即 ${PROJECT_NAME}_SOURCE_DIR，同 PROJECT_SOURCE_DIR
message(STATUS "PROJECT_BINARY_DIR : " ${PROJECT_BINARY_DIR}) # 项目的二进制目录，即 cmake 命令的目录，通常是 ${PROJECT_SOURCE_DIR}\build
message(STATUS "sub_BINARY_DIR   : " ${sub_BINARY_DIR})   # CMAKE 自动生成的变量，即 ${PROJECT_NAME}_BINARY_DIR，同 PROJECT_BINARY_DIR


message(STATUS "CMAKE_SOURCE_DIR   : " ${CMAKE_SOURCE_DIR})   #
message(STATUS "CMAKE_BINARY_DIR   : " ${CMAKE_BINARY_DIR})   #
message(STATUS "CMAKE_CURRENT_SOURCE_DIR : " ${CMAKE_CURRENT_SOURCE_DIR}) # 当前处理的 CMakeLists.txt 所在的路径
message(STATUS "CMAKE_CURRENT_BINARY_DIR : " ${CMAKE_CURRENT_BINARY_DIR}) # target 编译目录，
                                                                          # 使用 ADD_SURDIRECTORY(src bin) 可以更改此变量的值

add_executable(subapp main.cpp)