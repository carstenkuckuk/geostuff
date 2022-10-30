// Project: geostuff
// File: StreetAddressLatLongFile.cpp
//
// Reads StreetAddress objects plus lat long from a file or writes them to a file. The
// file format is a simple CSV file format 
//

#include "StreetAddressLatLongFile.hpp"

StreetAddressLatLongFile::StreetAddressLatLongFile()
	:m_fp(0), m_bOpenedForReading(false)
{
}

StreetAddressLatLongFile::~StreetAddressLatLongFile()
{
	if (m_bOpenedForReading)
	{
		fclose(m_fp);
		m_bOpenedForReading = false;
	}

}

bool StreetAddressLatLongFile::OpenForRead(const std::string &refstrFileName) // true=success, false=failure
{
	bool bSuccess = false;
	m_strFileName = refstrFileName;
	m_fp = fopen(refstrFileName.c_str(), "r");
	if (m_fp)
	{
		m_bOpenedForReading = true;
		bSuccess = true;
	}
	else
	{
		m_bOpenedForReading = false;
		bSuccess = false;
	}
	return bSuccess;
}


void StreetAddressLatLongFile::Close()
{
	if (m_bOpenedForReading)
	{
		fclose(m_fp);
		m_bOpenedForReading = false;
	}
}

bool StreetAddressLatLongFile::ReadStreetAddressLatLongFromFile(StreetAddress& refStreetAddress, double& refLat, double& refLong) // true=success, false=failure i.e. end of file reached
{
	bool bSuccess = false;
	if (m_bOpenedForReading)
	{
		double dLat = 0.0;
		double dLong = 0.0;
		char bufstrCountryCode[200]={0};
		char bufstrZip[200]={0};
		char bufstrCity[200]={0};
		char bufstrStreetname[200]={0};
		char bufstrStreetnumber[200]={0};
		char bufstrDescription[200]={0};

		int nRes =
			fscanf(m_fp,
				"%lf,%lf,%[^,\n],%[^,\n],%[^,\n],%[^,\n],%[^,\n],%[^,\n]\n",
				&dLat, &dLong, &bufstrCountryCode, &bufstrZip, &bufstrCity, &bufstrStreetname, &bufstrStreetnumber, &bufstrDescription
			);

		refLat = dLat;
		refLong = dLong;
		refStreetAddress.m_strCountryCode = bufstrCountryCode;
		refStreetAddress.m_strZip = bufstrZip;
		refStreetAddress.m_strCity = bufstrCity;
		refStreetAddress.m_strStreetname = bufstrStreetname;
		refStreetAddress.m_strStreetnumber = bufstrStreetnumber;
		refStreetAddress.m_strDescription = bufstrDescription;

		bSuccess = (nRes == 8);
	}

	return bSuccess;
}

bool StreetAddressLatLongFile::ReadStreetAddressesLatLongFromFile(std::vector<StreetAddress>& refrgStreetAddress, std::vector<double>& refrgLat, std::vector<double>& refrgLong)  // true=success, false=failure
{
	bool bFileEndReached = false;
	while (!bFileEndReached)
	{
		StreetAddress sa;
		double dLat = 0.0;
		double dLong = 0.0;
		bool bSuccess = ReadStreetAddressLatLongFromFile(sa, dLat, dLong);
		if (bSuccess)
		{
			refrgStreetAddress.push_back(sa);
			refrgLat.push_back(dLat);
			refrgLong.push_back(dLong);
		}
		else
		{
			bFileEndReached = true;
		}
	}
	return true;
}

