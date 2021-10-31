// File: svgfrommap.cpp
//
// Reads a map file and creates an .svg file from it
// 
// Initially it uses a fixed output size, and a fixed GPS area windoe


#include "../GPSObservation.hpp"
#include "../GPSTrackFile.hpp"
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

void ReadRoadmapfileAndWriteToSVGFile(const std::string strRoadmapFilename, const std::string strSVGFilename)
{
	Roadmap RM;
	ReadRoadmapFromFile(RM, strRoadmapFilename);

	SVGImage svg(
		/*dWidth_mm =*/ 297.0, /*dHeight_mm =*/ 210.0, // DIN A4 Quer
		/*dXMin =*/ 6.8976, /*dXMax =*/ 7.7120, // Ruhrgebiet: Hagen..Recklinghausen
		/*dYMin =*/ 51.3473, /*dYMax =*/ 51.6461); // Ruhrgebiet: Duisburg..Unna

	for (auto& rmc : RM.m_rgRoadmapConnections)
	{
		int nFromPointID = rmc.m_nFromPointID;
		int nToPointID = rmc.m_nToPointID;
		double dVelocity = rmc.m_nSumOfVelocitiesObserved / rmc.m_nWeight;
		RoadmapPoint ptFrom = RM.m_rgRoadmapPoints[nFromPointID];
		double dLong = ptFrom.m_dLong;
		double dLat = ptFrom.m_dLat;

		if ((0.0 <= dVelocity) && (dVelocity < 10.0))
		{
			// Fussgaenger 0..10 km/h
			svg.DiskAt(dLong, dLat, "green");
		}
		if ((10.0 <= dVelocity) && (dVelocity < 50.0))
		{
			// Strasse 10..50 km/h
			svg.DiskAt(dLong, dLat, "black");
		}
		if ((50.0 <= dVelocity) && (dVelocity < 300.0))
		{
			// Autobahn
			svg.DiskAt(dLong, dLat, "blue");
		}

	}

	svg.WriteToFile(strSVGFilename);
}


int main(int argc, const char** argv)
{
	int nRet = 0;

	std::string strWigleWifiFlename;
	std::string strRoadmapFilename;

	bool bParsedProperly = ParseCommandLine(strWigleWifiFlename, strRoadmapFilename, argc, argv);

	if (bParsedProperly)
	{
		ReadRoadmapfileAndWriteToSVGFile(strWigleWifiFlename, strRoadmapFilename);
	}
	else
	{
		std::cout << "Usage: svgfrommap <MapfileName> <SVGfileName>" << std::endl;
		nRet = 1;
	}

	return nRet;
}


