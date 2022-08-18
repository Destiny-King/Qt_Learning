cmake_minimum_required(VERSION 3.17)
project(Dial)

set(CMAKE_CXX_STANDARD 14)

set(EasyX_DIR C:/Software/mingw64)
include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib)

add_executable(Dial main.cpp tools.hpp)
target_link_libraries(Dial libeasyx.a libgdi32.a libole32.a winmm.a)