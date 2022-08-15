cmake_minimum_required(VERSION 3.17)
project(Dial)

set(CMAKE_CXX_STANDARD 11)

set(EasyX_DIR D:/Software/Tools/Cpp/easyx4mingw_20220610)
include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib64)

link_libraries(libeasyx.a libgdi32.a libole32.a)

add_executable(Dial main.cpp)