// distancefromlatlonglatlong.cpp
//
// Takes two GPS coordinates and outputs the distance in meters

#include "../GPSObservation.hpp"

#include <iostream>

bool ParseCommandLine(GPSObservation &refp1, GPSObservation &refp2, int argc, const char**argv)
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

	GPSObservation p1(51.4818445, 7.2162363);// Bochum
	GPSObservation p2(51.5135872, 7.4652981);// Dortmund

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
