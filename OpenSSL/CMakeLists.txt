cmake_minimum_required(VERSION 3.17)
project(OpenSSL)

set(CMAKE_CXX_STANDARD 14)

set(OpenSSL_DIR D:/Files/Libs/openssl)

include_directories(${OpenSSL_DIR}/include)
link_directories(${OpenSSL_DIR}/lib)
#link_libraries(libcrypto openssl)
add_executable(OpenSSL main.cpp)
target_link_libraries(OpenSSL openssl libcrypto)