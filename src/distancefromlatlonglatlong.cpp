// distancefromlatlonglatlong.cpp
//
// Takes two GPS coordinates and outputs the distance in meters
#include <cmath>
#include <iostream>
#include "distancefromlatlonglatlong.h"
static const double pi = 3.14159265358979323846;

class GPSCoordinate
{
public:
	GPSCoordinate(double dLat=0.0, double dLong=0.0) :m_dLat(dLat), m_dLong(dLong) {};

	double m_dLat; // degrees
	double m_dLong; // degrees
};


double DegreesToRadians(double dDegrees)
{
	return dDegrees / 180.0 * pi;
}


double DinstanceInMeters(const GPSCoordinate &p1, const GPSCoordinate &p2)
{
	// Altmeister: https://stackoverflow.com/questions/27126714/c-latitude-and-longitude-distance-calculator
	double dLat1InRad = DegreesToRadians(p1.m_dLat);
	double dLong1InRad = DegreesToRadians(p1.m_dLong);
	double dLat2InRad = DegreesToRadians(p2.m_dLat);
	double dLong2InRad = DegreesToRadians(p2.m_dLong);

	double d = 6371.0 * acos(sin(dLat1InRad) * sin(dLat2InRad) + cos(dLat1InRad) * cos(dLat2InRad) * cos(dLong1InRad - dLong2InRad));

	return d*1000.0;
}

bool ParseCommandLine(GPSCoordinate &refp1, GPSCoordinate &refp2, int argc, const char**argv)
{
	bool bOk = argc == 5;
	if (bOk)
	{
		sscanf(argv[1], "%lf", &refp1.m_dLat);
		sscanf(argv[2], "%lf", &refp1.m_dLong);
		sscanf(argv[3], "%lf", &refp2.m_dLat);
		sscanf(argv[4], "%lf", &refp2.m_dLong);
	}

	return bOk;
}

int main(int argc, const char** argv)
{
	int nRet = 0;

	GPSCoordinate p1(51.4818445, 7.2162363);// Bochum
	GPSCoordinate p2(51.5135872, 7.4652981);// Dortmund

//	51.4818445 7.2162363 51.5135872 7.4652981


	bool bParsedProperly = ParseCommandLine(p1, p2, argc, argv);

	if (bParsedProperly)
	{
		double d = DinstanceInMeters(p1, p2);
		std::cout << d << std::endl;

	}
	else
	{
		std::cout << "Usage: distancefromlatlonglatlong <lat1> <long1> <lat2> <long2>" << std::endl;
		nRet = 1;
	}

	return nRet;
}
