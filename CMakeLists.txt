cmake_minimum_required(VERSION 3.9.6)

project(geostuff)

set(CMAKE_BUILD_TYPE Release)

add_executable(distancefromlatlonglatlong
	src/GPSObservation.cpp
	src/GPSObservation.hpp
    src/tools/distancefromlatlonglatlong.cpp
)

