cmake_minimum_required(VERSION 3.17)
project(openCV)

set(CMAKE_CXX_STANDARD 14)

#set(INC_DIR D:/Files/Libs/opencv/mingw-build/include)
#set(LINK_DIR D:/Files/Libs/opencv/mingw-build/x64/mingw/lib)
#
#include_directories(${INC_DIR})
#link_directories(${LINK_DIR})
#add_executable(openCV main.cpp)
#target_link_libraries(openCV libopencv_core411.dll.a libopencv_highgui411.dll.a
#        libopencv_imgcodecs411.dll.a libopencv_imgproc411.dll.a
#        libopencv_features2d411.dll.a libopencv_calib3d411.dll.a)

add_executable(openCV main.cpp)
set(OpenCV_DIR D:/Files/Libs/opencv/mingw-build)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(openCV ${OpenCV_LIBRARIES})