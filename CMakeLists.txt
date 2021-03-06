cmake_minimum_required(VERSION 2.8)
project(iotivity_weeder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("../iotivity-1.1.0/resource/include" "../iotivity-1.1.0/resource/csdk/stack/include" "../iotivity-1.1.0/resource/c_common")
include_directories("../iotivity-1.1.0/resource/csdk/security/include" "../iotivity-1.1.0/resource/csdk/connectivity/inc" "../iotivity-1.1.0/resource/oc_logger/include")

link_directories("~/development/iotivity-1.1.0/out/linux/x86_64/release")
link_directories("~/development/mraa/build/src")


set(SOURCE_FILES
    main.cpp
    Makefile
    namedefs.h
    WeederObserver.h
    WeederObserver.cpp
    weederServer.cpp
    weederServer.h sensors.h CSensor.cpp CSensor.h TemperatureSensor.cpp TemperatureSensor.h MoistSensor.cpp MoistSensor.h)

add_executable(weeder ${SOURCE_FILES} CSensor.cpp CSensor.h MoistSensor.cpp MoistSensor.h)
target_link_libraries(weeder oc octbstack logger coap c_common ocsrm mraa pthread)
