cmake_minimum_required(VERSION 3.15)
project(TestModernCPP)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. SRCS)

add_executable(${PROJECT_NAME} ${SRCS})