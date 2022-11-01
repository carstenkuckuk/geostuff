// Project: geostuff
// File: GeolocationFromFiledata.hpp
//
// Reads geolocation data from a file and implements geolocation API based on that
//

#ifndef __GEOSTUFF_GEOLOCATIONFROMFILEDATA_HPP__
#define __GEOSTUFF_GEOLOCATIONFROMFILEDATA_HPP__

#include "StreetAddress.hpp"
#include <string>
#include <vector>

class GeolocationFromFiledata
{
public:
	void LoadDataFromFile(const std::string &refstrGeodataFilename);
	void InsertStreetAddressLatLong(const StreetAddress& refsa, double dLat, double dLong);

	std::pair<StreetAddress, double> GetStreetAddressByLatitudeLongitude(double dLat, double dLong); // Adresse plus Distanz in Metern

protected:
	std::vector<StreetAddress> m_rgStreetAddress;
	std::vector<double> m_rgLat;
	std::vector<double> m_rgLong;
};


#endif
