// File: addtrackfiletomap.cpp
//
// Loads a Map, and adds the observations from the trackfile to this map, and then saves the map
// 



#include "../GPSObservation.hpp"
#include "../GPSTrackFile.hpp"
#include "../Mapbuilder.hpp"
#include "../SVGImage.hpp"
#include "../Roadmap.hpp"

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

void ReadGPSTrackfileAndAddToMapfile(const std::string strMapfilename, const std::string strGPSTrackFilename)
{
	Roadmap RM;
	ReadRoadmapFromFile(RM, strMapfilename);

	std::vector<GPSObservation> rgGPSObservations;
	GPSTrackFile tf;
	tf.OpenForRead(strGPSTrackFilename);
	tf.ReadGPSObservationsFromFile(rgGPSObservations);
	tf.Close();

	MapBuilder MB(RM);

	GPSObservation oLastObs;

	for (auto o : rgGPSObservations)
	{
		MB.FeedGPSObservation(o);
	}

	WriteRoadmapToFile(RM, strMapfilename);
}


int main(int argc, const char** argv)
{
	int nRet = 0;

	std::string strMapfilename;
	std::string strGPSTrackFilename;

	bool bParsedProperly = ParseCommandLine(strGPSTrackFilename, strMapfilename, argc, argv);

	if (bParsedProperly)
	{
		ReadGPSTrackfileAndAddToMapfile(strMapfilename, strGPSTrackFilename);
	}
	else
	{
		std::cout << "Usage: addtrackfiletomap <GPSTrackfileName> <MapfileName>" << std::endl;
		nRet = 1;
	}

	return nRet;
}


