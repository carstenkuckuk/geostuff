// wiglewifistats.cpp
//
// Reads some interesting stats from a WigleWifie SQLite database file and displays it.

// For distance calculation functions:
#include "../GPSObservation.hpp"

#include "../WigleWifiDatabase.hpp"

#include <vector>
#include <string>
#include <iostream>

bool ParseCommandLine(std::string &refstrFilename,  int argc, const char**argv)
{
	bool bOk = argc == 2;
	if (bOk)
	{
		refstrFilename = argv[1];
	}

	return bOk;
}

void ReadWigleWifiStats(const std::string strWigleWifiFilename)
{
	WigleWifiDatabase wwdb;
	wwdb.Open(strWigleWifiFilename);

	std::cout << "Statistics for Wigle Wifi SQLite database '" << strWigleWifiFilename.c_str() << "'" << std::endl;

	int nLocations = wwdb.SelectAsInt64("select count(*) from location");
	std::cout << "Number of locations: " << nLocations << std::endl;

	int nLocationsWithTimeEqualsZero = wwdb.SelectAsInt64("select count(*) from location where time=0;");
	std::cout << "Number of locations without proper timestamp: " << nLocationsWithTimeEqualsZero << std::endl;

	__int64 nMinDatetime = wwdb.SelectAsInt64("select min(time) from (select time from location where time<>0)");
	std::cout << "Earliest location is from " << DateTimeToString(nMinDatetime).c_str() << " (" << nMinDatetime << ")" << std::endl;

	__int64 nMaxDatetime = wwdb.SelectAsInt64("select max(time) from location");
	std::cout << "Latest location is from " << DateTimeToString(nMaxDatetime).c_str() << "(" << nMaxDatetime << ")" << std::endl;

	double dMinLat = wwdb.SelectAsDouble("select min(lat) from location");
	double dMaxLat = wwdb.SelectAsDouble("select max(lat) from location");
	double dMinLon = wwdb.SelectAsDouble("select min(lon) from location");
	double dMaxLon = wwdb.SelectAsDouble("select max(lon) from location");

	GPSObservation oMin(0, dMinLat, dMinLon);
	GPSObservation oMax(0, dMaxLat, dMaxLon);
	GPSObservation oEcke1(0, dMaxLat, dMinLon);
	GPSObservation oEcke2(0, dMinLat, dMaxLon);

	double dDistanceLat_km = DinstanceInMeters(oMin, oEcke1) / 1000.0;
	double dDistanceLon_km = DinstanceInMeters(oMin, oEcke2) / 1000.0;
	double dDiameter_km = DinstanceInMeters(oMin, oMax) / 1000.0;

	std::cout << "Latitude covered: "  << dMinLat << " .. " << dMaxLat << " (" << dDistanceLat_km << " km)" << std::endl;
	std::cout << "Longitude covered: " << dMinLon << " .. " << dMaxLon << " (" << dDistanceLon_km << " km)" << std::endl;
	std::cout << "Diameter of the covered rectangle is " << dDiameter_km << " km" << std::endl;

	wwdb.Close();

}


int main(int argc, const char** argv)
{
	int nRet = 0;

	std::string strWigleWifiFlename;

	bool bParsedProperly = ParseCommandLine(strWigleWifiFlename, argc, argv);

	if (bParsedProperly)
	{
		ReadWigleWifiStats(strWigleWifiFlename);
	}
	else
	{
		std::cout << "Usage: wiglewifistats <WigleWifeFilename>" << std::endl;
		nRet = 1;
	}

	return nRet;
}
