cmake_minimum_required(VERSION 3.9.6)

project(geostuff)

set(CMAKE_BUILD_TYPE Release)

INCLUDE_DIRECTORIES(
	libs/gtest-1.7.0/include
	libs/gtest-1.7.0
	libs/sqlite-amalgamation-3081002
)

add_subdirectory(src)



add_executable(distancefromlatlonglatlong
	src/GPSObservation.cpp
	src/GPSObservation.hpp
    src/tools/distancefromlatlonglatlong.cpp
)

