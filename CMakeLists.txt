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


add_executable(svgfromlabellist
	src/GPSObservation.cpp
	src/GPSObservation.hpp
	src/GPSTrackFile.cpp
	src/GPSTrackFile.hpp
	src/SVGImage.cpp
	src/SVGImage.hpp

    src/tools/svgfromlabellist.cpp
)

add_executable(svgfromstackofsvgs
	src/SVGImage.cpp
	src/SVGImage.hpp

    src/tools/svgfromstackofsvgs.cpp
)

add_executable(svgfromtrackfile
	src/GPSObservation.cpp
	src/GPSObservation.hpp
	src/GPSTrackFile.cpp
	src/GPSTrackFile.hpp
	src/SVGImage.cpp
	src/SVGImage.hpp

    src/tools/svgfromtrackfile.cpp
)

add_executable(svgfrommap
	src/GPSObservation.cpp
	src/GPSObservation.hpp
	src/GPSTrackFile.cpp
	src/GPSTrackFile.hpp
	src/Roadmap.cpp
	src/Roadmap.hpp
	src/SVGImage.cpp
	src/SVGImage.hpp

    src/tools/svgfrommap.cpp
)

add_executable(addtrackfiletomap
	src/GPSObservation.cpp
	src/GPSObservation.hpp
	src/GPSTrackFile.cpp
	src/GPSTrackFile.hpp
	src/MapBuilder.cpp
	src/MapBuilder.hpp
	src/Roadmap.cpp
	src/Roadmap.hpp
	src/SVGImage.cpp
	src/SVGImage.hpp

    src/tools/addtrackfiletomap.cpp
)



add_executable(wiglewifistats
	src/GPSObservation.cpp
	src/GPSObservation.hpp
	src/WigleWifiDatabase.cpp
	src/WigleWifiDatabase.hpp

	libs/sqlite-amalgamation-3081002/sqlite3.c
	libs/sqlite-amalgamation-3081002/sqlite3.h

    src/tools/wiglewifistats.cpp
)

add_executable(wiglewifitotrackfile
	src/GPSObservation.cpp
	src/GPSObservation.hpp
	src/GPSTrackFile.cpp
	src/GPSTrackFile.hpp
	src/WigleWifiDatabase.cpp
	src/WigleWifiDatabase.hpp

	libs/sqlite-amalgamation-3081002/sqlite3.c
	libs/sqlite-amalgamation-3081002/sqlite3.h

    src/tools/wiglewifitotrackfile.cpp
)

add_executable(sqlite3
	libs/sqlite-amalgamation-3081002/shell.c
	libs/sqlite-amalgamation-3081002/sqlite3.c
	libs/sqlite-amalgamation-3081002/sqlite3.h
)


