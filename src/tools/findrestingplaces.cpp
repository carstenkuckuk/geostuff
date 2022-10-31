// File: findrestingplaces.cpp
//
// Takes a trackfile and determines locations where s/h/it stayed within 20 meters for more than 10 minutes.
//
// Initially, uses locations from a file

#include "../StreetAddress.hpp"
#include "../GeolocationFromFiledata.hpp"
#include "../GPSTrackFile.hpp"
#include "../RestingplaceFinder.hpp"

#include <string>
#include <iostream>

bool ParseCommandLine(std::string& refstrTrackfileFilename, std::string &refstrGeodataFilename, int argc, const char** argv)
{
	bool bOk = argc == 3;
	if (bOk)
	{
		refstrTrackfileFilename = argv[1];
		refstrGeodataFilename = argv[2];
	}

	return bOk;
}

void FindRestingPlacesInTrackfileAndPrintThemUsingGeodatafile(const std::string &refstrTrackfileFilename, const std::string &refstrGeodataFilename)
{
	RestingplaceFinder rpf;

	GPSTrackFile gtf;
	bool bEsGibtNochWasZuLesen = gtf.OpenForRead(refstrTrackfileFilename);
	int nGPSObservationsRead = 0;
	while (bEsGibtNochWasZuLesen)
	{
		GPSObservation go;
		bEsGibtNochWasZuLesen = gtf.ReadGPSObservationFromFile(go);
		if (bEsGibtNochWasZuLesen)
		{
			nGPSObservationsRead++;
			rpf.ProcessGPSObservation(go);
		}
	}
	gtf.Close();

	GeolocationFromFiledata glfd;
	glfd.LoadDataFromFile(refstrGeodataFilename);

	std::vector<Restingplace> rgRP = rpf.GetRestingplaces();
	for (Restingplace rp : rgRP)
	{
		double dLat = rp.GetLat();
		double dLong = rp.GetLong();
//		time_t tmFrom = rp.GetTimeFrom();
//		time_t tmTo = rp.GetTimeTo();
		StreetAddress sa = glfd.GetStreetAddressByLatitudeLongitude(dLat, dLong);
		std::string strSA = toString(sa);

		std::cout << "(" << dLat << "," << dLong << ") " << strSA << std::endl;
	}


}


int main(int argc, const char** argv)
{
	int nRet = 0;

	std::string strTrackfileFilename;
	std::string strGeodataFilename;

	bool bParsedProperly = ParseCommandLine(strTrackfileFilename, strGeodataFilename, argc, argv);

	if (bParsedProperly)
	{
		FindRestingPlacesInTrackfileAndPrintThemUsingGeodatafile(strTrackfileFilename, strGeodataFilename);
	}
	else
	{
		std::cout << "Usage: findrestingplaces <trackfile> [<geodatafilename>]" << std::endl;
		nRet = 1;
	}

	return nRet;
}


