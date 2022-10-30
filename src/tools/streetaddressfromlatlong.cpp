// File: streetaddressfromlatlong.cpp
//
// Takes latitude longitude and determines the nearest street address
//
// Initially, uses locations from a file

#include "../StreetAddress.hpp"
#include "../GeolocationFromFiledata.hpp"

#include <string>
#include <iostream>

bool ParseCommandLine(std::string& refstrFilename, double& refdLat, double& refdLong, int argc, const char** argv)
{
	bool bOk = argc == 4;
	if (bOk)
	{
		refstrFilename = argv[1];
		refdLat = atof(argv[2]);
		refdLong = atof(argv[3]);
	}

	return bOk;
}

void ReadGeodatafileAndDetermineStreetAddressForGivenLatitudeLongitude(const std::string strGeodataFilename, double dLat, double dLong)
{
	GeolocationFromFiledata glfd;
	glfd.LoadDataFromFile(strGeodataFilename);
	StreetAddress sa = glfd.GetStreetAddressByLatitudeLongitude(dLat, dLong);
	std::cout << toString(sa);
}


int main(int argc, const char** argv)
{
	int nRet = 0;

	std::string strGeodataFilename;
	double dLat = 0.0;
	double dLong = 0.0;

	bool bParsedProperly = ParseCommandLine(strGeodataFilename, dLat, dLong, argc, argv);

	if (bParsedProperly)
	{
		ReadGeodatafileAndDetermineStreetAddressForGivenLatitudeLongitude(strGeodataFilename, dLat, dLong);
	}
	else
	{
		std::cout << "Usage: streetaddressfromlatlong <Geodatafilename> <Latitude> <Longitude>" << std::endl;
		nRet = 1;
	}

	return nRet;
}


