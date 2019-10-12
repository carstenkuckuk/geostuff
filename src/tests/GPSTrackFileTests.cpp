// Datei: GPSTrackFileTests.cpp
//
// Unittests für ./src/GPSTrackFile.hpp/cpp

// DUT:
#include "../GPSTrackFile.hpp"


// Google Test Library:
#include "gtest/gtest.h"

#include "../GPSObservation.hpp"

TEST(GPSTrackFileTests, WriteToFileThenReadFromFile)
{
	GPSObservation goBochum(0, 51.4818445, 7.2162363,0,0,"Bochum");
	GPSObservation goDortmund(0, 51.5135872, 7.4652981,0,0,"Dortmund");
	GPSObservation goRecklinghausen(0, 51.6140649, 7.1979453,0,0,"Recklinghausen");
	GPSObservation goHirtshals(0, 57.588120, 9.959220,0,0,"Hirtshals");

	GPSTrackFile gtf1;
	gtf1.OpenForWrite("GPSTrackFileTests.trackfile");
	gtf1.WriteGPSObservationToFile(goBochum);
	gtf1.WriteGPSObservationToFile(goDortmund);
	gtf1.WriteGPSObservationToFile(goRecklinghausen);
	gtf1.WriteGPSObservationToFile(goHirtshals);
	gtf1.Close();

	GPSTrackFile gtf2;
	GPSObservation o1, o2, o3, o4, o5;
	gtf2.OpenForRead("GPSTrackFileTests.trackfile");
	bool r1 = gtf2.ReadGPSObservationFromFile(o1);
	ASSERT_TRUE(r1);
	ASSERT_EQ(o1, goBochum);

	bool r2 = gtf2.ReadGPSObservationFromFile(o2);
	ASSERT_TRUE(r2);
	ASSERT_EQ(o2, goDortmund);

	bool r3 = gtf2.ReadGPSObservationFromFile(o3);
	ASSERT_TRUE(r3);
	ASSERT_EQ(o3, goRecklinghausen);

	bool r4 = gtf2.ReadGPSObservationFromFile(o4);
	ASSERT_TRUE(r4);
	ASSERT_EQ(o4, goHirtshals);

	bool r5 = gtf2.ReadGPSObservationFromFile(o5);
	ASSERT_FALSE(r5);


}
