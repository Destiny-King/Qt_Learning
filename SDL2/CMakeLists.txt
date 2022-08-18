cmake_minimum_required(VERSION 3.17)
project(SDL2)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_DIR D:/Files/Libs/SDL2)

include_directories(${SDL2_DIR}/include)
link_directories(${SDL2_DIR}/lib/x64)
add_executable(SDL2 main.cpp)
target_link_libraries(SDL2 SDL2.lib SDL2_image.lib)
