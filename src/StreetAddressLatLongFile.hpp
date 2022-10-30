// Project: geostuff
// File: StreetAddressLatLongFile.hpp
//
// Reads Street Addresses and the related latitudes and longitudes from a file
//
#ifndef __GEOSTUFF_STREETADDRESSLATLONGFILE_HPP__
#define __GEOSTUFF_STREETADDRESSLATLONGFILE_HPP__

#include "StreetAddress.hpp"

#include <string>
#include <vector>
// Fuer den FILE-Pointer:
#include <stdio.h>

class StreetAddressLatLongFile
{
public:
	StreetAddressLatLongFile();
	virtual ~StreetAddressLatLongFile();

	virtual bool OpenForRead(const std::string &refstrFileName); // true=success, false=failure
	virtual void Close();

	virtual bool ReadStreetAddressesLatLongFromFile(std::vector<StreetAddress>& refrgStreetAddress, std::vector<double>& refrgLat, std::vector<double>& refrgLong);
	virtual bool ReadStreetAddressLatLongFromFile(StreetAddress& refStreetAddress, double& refLat, double& refLong);

	std::string m_strFileName;
	FILE *m_fp;
	bool m_bOpenedForReading;
};


#endif
