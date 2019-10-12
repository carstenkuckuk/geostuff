// Datei: GPSObservationTests.cpp
//
// Unittests für ./src/GPSObservation.hpp/cpp

// DUT:
#include "../GPSObservation.hpp"


// Google Test Library:
#include "gtest/gtest.h"
TEST(GPSObservationTests, OperatorEquals)
{
	GPSObservation goBochum(51.4818445, 7.2162363);
	GPSObservation goBochum2(51.4818445, 7.2162363);
	GPSObservation goDortmund(51.5135872, 7.4652981);

	ASSERT_TRUE(goBochum == goBochum);
	ASSERT_TRUE(goBochum == goBochum2);

	ASSERT_FALSE(goBochum == goDortmund);
}

TEST(GPSObservationTests, DinstanceInMeters)
{
	GPSObservation goBochum(0, 51.4818445, 7.2162363);
	GPSObservation goDortmund(0, 51.5135872, 7.4652981);
	GPSObservation goRecklinghausen(0, 51.6140649, 7.1979453);
	GPSObservation goHirtshals(0, 57.588120, 9.959220);

	double dBochumDortmund = DinstanceInMeters(goBochum, goDortmund);
	double dDortmundBochum = DinstanceInMeters(goDortmund, goBochum);

	ASSERT_NEAR(17598.6179, dBochumDortmund, 0.1);

	ASSERT_NEAR(dDortmundBochum, dBochumDortmund, 0.001);

	double dBochumRecklinghausen = DinstanceInMeters(goBochum, goRecklinghausen);
	ASSERT_NEAR(14756.5393, dBochumRecklinghausen, 0.1);

	double dBochumHirtshals = DinstanceInMeters(goBochum, goHirtshals);
	ASSERT_NEAR(701520.6178, dBochumHirtshals, 0.1); 
	// https://www.luftlinie.org/Hirtshals,Hj%C3%B8rring,Nordjylland,DNK/Bochum gibt 701.70 km an, wir errechnen 701.52km. 
	// Ein Rechenfehler von 200m auf 700km ist gut genug für unser Hackprojekt

}
