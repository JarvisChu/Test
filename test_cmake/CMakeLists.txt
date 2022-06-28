cmake_minimum_required(VERSION 3.15)

project(hello)

############ project 项目相关变量 ############

message(STATUS "PROJECT_NAME       : " ${PROJECT_NAME})       # 项目名称，即 project() 中设置，即hello
message(STATUS "PROJECT_SOURCE_DIR : " ${PROJECT_SOURCE_DIR}) # 项目目录
message(STATUS "hello_SOURCE_DIR   : " ${hello_SOURCE_DIR})   # CMAKE 自动生成的变量，即 ${PROJECT_NAME}_SOURCE_DIR，同 PROJECT_SOURCE_DIR
message(STATUS "PROJECT_BINARY_DIR : " ${PROJECT_BINARY_DIR}) # 项目的二进制目录，即 cmake 命令的目录，通常是 ${PROJECT_SOURCE_DIR}\build
message(STATUS "hello_BINARY_DIR   : " ${hello_BINARY_DIR})   # CMAKE 自动生成的变量，即 ${PROJECT_NAME}_BINARY_DIR，同 PROJECT_BINARY_DIR


message(STATUS "CMAKE_SOURCE_DIR   : " ${CMAKE_SOURCE_DIR})   #
message(STATUS "CMAKE_BINARY_DIR   : " ${CMAKE_BINARY_DIR})   #
message(STATUS "CMAKE_CURRENT_SOURCE_DIR : " ${CMAKE_CURRENT_SOURCE_DIR}) # 当前处理的 CMakeLists.txt 所在的路径
message(STATUS "CMAKE_CURRENT_BINARY_DIR : " ${CMAKE_CURRENT_BINARY_DIR}) # target 编译目录，
                                                                          # 使用 ADD_SURDIRECTORY(src bin) 可以更改此变量的值
                                                                          # SET(EXECUTABLE_OUTPUT_PATH <新路径>) 并不会对此变量有影响,只是改变了最终目标文件的存储路径

# 比较 PROJECT_SOURCE_DIR 和 CMAKE_SOURCE_DIR
# PROJECT_SOURCE_DIR 始终是由距离它最近的 project() 来决定，
#     即通过 add_subdirectory() 添加的子目录中，如果也定义了 project()，
#     那么 子目录中的 PROJECT_SOURCE_DIR 就是子目录的路径
# CMAKE_SOURCE_DIR   始终是最外层的CMakeLists.txt所在目录，子目录中也一样
 
当不是使用 add_subdirectory() 时，两种是相同的
# 如果是使用 add_subdirectory() 添加子目录，

############ 系统相关变量 ############

message(STATUS "CMAKE_SYSTEM          : " ${CMAKE_SYSTEM})           # 系统名称，e.g. Linux-2.6.22
message(STATUS "CMAKE_SYSTEM_NAME     : " ${CMAKE_SYSTEM_NAME})      # 系统名称，e.g. Linux、FreeBSD、Windows、Darwin、Android
message(STATUS "CMAKE_SYSTEM_VERSION  : " ${CMAKE_SYSTEM_VERSION})   # 系统版本，e.g. 2.6.22
message(STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR}) # 处理器名称，e.g. x86_64

if(UNIX)       # UNIX 系统，包括 OSX，Linux，cygwin 等
    message(STATUS "UNIX defined")
elseif (WIN32) # WIN32 平台，包括 cygwin
    message(STATUS "WIN32 defined")
endif()

if (APPLE) # APPLE 系统，包括 MacOS X or iOS, watchOS, tvOS (since 3.10.3)
    message(STATUS "APPLE defined")
endif()

if(UNIX AND NOT APPLE) #
    message(STATUS "Linux, BSD, Solaris, Minix ...")
endif()



# 编译器相关变量
message(STATUS "CMAKE_C_COMPILER          : " ${CMAKE_C_COMPILER})

if(MSVC OR MSYS OR MINGW)
    # for detecting Windows compilers
    message(STATUS "MSVC OR MSYS OR MINGW defined")
endif()

add_subdirectory(sub)

add_executable(helloapp main.cpp)