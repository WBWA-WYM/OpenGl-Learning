#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)
#本工程的名字
project(OpenGL)
#本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)
#往项目里加入一个全局的预编译宏s
add_definitions(-DDEBUG)

file(GLOB ASSETS "./assets")

file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

#包括目录
include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
)
#链接目录
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)
#添加子目录
add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)
#本工程所有cpp文件编译链接，生成exe
add_executable(openglStudy "main.cpp" "glad.c")
#链接库
target_link_libraries(openglStudy glfw3 wrapper app fw)







