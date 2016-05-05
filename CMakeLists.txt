cmake_minimum_required(VERSION 3.5)
project(iotivity_weeder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    iotivity-weeder_0.1.bb
    main.cpp
    Makefile
    namedefs.h
    weederServer.cpp
    weederServer.h)

add_executable(iotivity_weeder ${SOURCE_FILES})