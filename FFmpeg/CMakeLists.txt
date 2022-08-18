cmake_minimum_required(VERSION 3.17)
project(FFmpeg)

set(CMAKE_CXX_STANDARD 14)

set(FFmpeg_DIR D:/Files/Libs/ffmpeg)

include_directories(${FFmpeg_DIR}/include)
link_directories(${FFmpeg_DIR}/lib)
add_executable(FFmpeg main.cpp)
target_link_libraries(FFmpeg avcodec.lib avdevice.lib avfilter.lib avformat.lib
        avutil.lib postproc.lib swresample.lib swscale.lib)
