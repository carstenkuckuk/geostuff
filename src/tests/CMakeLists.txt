add_executable(tests
#DUTs:
	../GPSObservation.cpp
	../GPSObservation.hpp
#Unittests:
	GPSObservationTests.cpp
#Hauptprogramm:
	../../libs/gtest-1.7.0/src/gtest-all.cc
    TestsMain.cpp

)

