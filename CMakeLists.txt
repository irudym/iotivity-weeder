cmake_minimum_required(VERSION 3.5)
project(iotivity_weeder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("../iotivity-1.1.0/resource/include" "../iotivity-1.1.0/resource/c_common" "../iotivity-1.1.0/resource/csdk/logger" )
include_directories("../iotivity-1.1.0/resource/csdk/stack/include")

set(SOURCE_FILES
    main.cpp
    Makefile
    namedefs.h
    weederServer.cpp
    weederServer.h sensors.h)

add_executable(weeder ${SOURCE_FILES})