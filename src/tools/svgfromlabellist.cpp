// File: svgfromlabellist.cpp
//
// Takes a labellist and creates an .svg file from it
// 
// Initially it uses a fixed output size, and a fixed GPS area windoe


#include "../GPSObservation.hpp"
#include "../GPSTrackFile.hpp"
#include "../SVGImage.hpp"

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

void ReadLabellistAndWriteToSVGFile(const std::string strGPSTrackFilename, const std::string strSVGFilename)
{
	std::vector<GPSObservation> rgGPSObservations;

	GPSTrackFile tf;
	tf.OpenForRead(strGPSTrackFilename);
	tf.ReadGPSObservationsFromFile(rgGPSObservations);
	tf.Close();

	SVGImage svg(
		/*dWidth_mm =*/ 297.0, /*dHeight_mm =*/ 210.0, // DIN A4 Quer
		/*dXMin =*/ 6.8976, /*dXMax =*/ 7.7120, // Ruhrgebiet: Hagen..Recklinghausen
		/*dYMin =*/ 51.3473, /*dYMax =*/ 51.6461); // Ruhrgebiet: Duisburg..Unna

	for (auto o : rgGPSObservations)
	{
		svg.TextAt(o.m_dLong, o.m_dLat, o.m_strComment);
	}

	svg.WriteToFile(strSVGFilename);
}


int main(int argc, const char** argv)
{
	int nRet = 0;

	std::string strWigleWifiFlename;
	std::string strGPSTrackFilename;

	bool bParsedProperly = ParseCommandLine(strWigleWifiFlename, strGPSTrackFilename, argc, argv);

	if (bParsedProperly)
	{
		ReadLabellistAndWriteToSVGFile(strWigleWifiFlename, strGPSTrackFilename);
	}
	else
	{
		std::cout << "Usage: svgfromlabellist <Labellistfilename> <SVGfileName>" << std::endl;
		nRet = 1;
	}

	return nRet;
}


