add_executable(tests
#DUTs:
	../GPSObservation.cpp
	../GPSObservation.hpp
	../GPSTrackFile.cpp
	../GPSTrackFile.hpp
#Unittests:
	GPSObservationTests.cpp
	GPSTrackFileTests.cpp
#Hauptprogramm:
	../../libs/gtest-1.7.0/src/gtest-all.cc
    TestsMain.cpp

)

