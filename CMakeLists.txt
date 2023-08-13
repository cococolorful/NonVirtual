cmake_minimum_required(VERSION 3.12)

project(TestNonVirtual)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Sandbox
    src/main.cpp
)

target_include_directories(Sandbox PRIVATE include)

# target_link_libraries(YourExecutableName 
#     # 添加库
#     library1
#     library2
# )

# 设置构建输出目录
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
