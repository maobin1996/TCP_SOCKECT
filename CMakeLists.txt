cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(sonar_F)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件
add_executable(server src/server.cpp)  
add_executable(client src/main.cpp src/client.cpp)  

include_directories(include) 
# add_executable(server src/server.cpp)
# add_executable(client src/client.cpp)
# add_executable(client src/main.cpp)
# add_executable(client include/client.h)
# Windows 特定设置
if(WIN32)
    target_link_libraries(server ws2_32)
    target_link_libraries(client ws2_32)
endif()




