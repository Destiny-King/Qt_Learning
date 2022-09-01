cmake_minimum_required(VERSION 3.17)
project(WhiteBlock)

set(CMAKE_CXX_STANDARD 14)

set(EasyX_DIR C:/Software/mingw64)
include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib)

add_executable(WhiteBlock main.cpp)
target_link_libraries(WhiteBlock libeasyx.a libgdi32.a libole32.a winmm.a)