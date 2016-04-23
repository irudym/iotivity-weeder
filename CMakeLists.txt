cmake_minimum_required(VERSION 3.5)
project(weeder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("../iotivity-1.1.0/resource/include" "../iotivity-1.1.0/resource/csdk/stack/include" "../iotivity-1.1.0/resource/c_common")
include_directories("../iotivity-1.1.0/resource/csdk/security/include" "../iotivity-1.1.0/resource/csdk/connectivity/inc" "../iotivity-1.1.0/resource/oc_logger/include")

link_directories("../iotivity-1.1.0/out/darwin/x86_64/release")

set(SOURCE_FILES main.cpp weederServer.cpp namedefs.h)
add_executable(weeder ${SOURCE_FILES})
target_link_libraries(weeder octbstack logger)