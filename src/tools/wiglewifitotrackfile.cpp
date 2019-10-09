// wiglewifitotrackfile.cpp
//
// Reads the locations from a WigleWifi SQLite database and writes them to a track file

#include "../GPSObservation.hpp"
#include "../GPSTrackFile.hpp"
#include "../WigleWifiDatabase.hpp"

#include <vector>
#include <string>
#include <iostream>

bool ParseCommandLine(std::string &refstrFilename1, std::string &refstrFilename2, int argc, const char**argv)
{
	bool bOk = argc == 3;
	if (bOk)
	{
		refstrFilename1 = argv[1];
		refstrFilename2 = argv[2];
	}

	return bOk;
}

void ReadWigleWifiLocationsAndWriteThemToGPSTrackfile(const std::string strWigleWifiFilename, const std::string strGPSTrackFilename)
{
	WigleWifiDatabase wwdb;
	wwdb.Open(strWigleWifiFilename);
	std::vector<GPSObservation> rgGPSObservations;
	wwdb.ReadAllGPSObservations(rgGPSObservations);
	wwdb.Close();

	GPSTrackFile tf;
	tf.OpenForWrite(strGPSTrackFilename);
	tf.WriteGPSObservationsToFile(rgGPSObservations);
	tf.Close();
}


int main(int argc, const char** argv)
{
	int nRet = 0;

	std::string strWigleWifiFlename;
	std::string strGPSTrackFilename;

	bool bParsedProperly = ParseCommandLine(strWigleWifiFlename, strGPSTrackFilename, argc, argv);

	if (bParsedProperly)
	{
		ReadWigleWifiLocationsAndWriteThemToGPSTrackfile(strWigleWifiFlename, strGPSTrackFilename);
	}
	else
	{
		std::cout << "Usage: wiglewifitotrackfile <WigleWifeFilename> <GPSTrackfileName>" << std::endl;
		nRet = 1;
	}

	return nRet;
}
