// Project: geostuff
// File: GeolocationFromFiledata.cpp
//
// Reads geolocation data from a file and implements geolocation API based on that
//

#include "GeolocationFromFiledata.hpp"
#include "StreetAddressLatLongFile.hpp"

void  GeolocationFromFiledata::LoadDataFromFile(const std::string& refstrGeodataFilename)
{
	StreetAddressLatLongFile sallf;
	sallf.OpenForRead(refstrGeodataFilename);
	sallf.ReadStreetAddressesLatLongFromFile(m_rgStreetAddress, m_rgLat, m_rgLong);
	sallf.Close();

}

void GeolocationFromFiledata::InsertStreetAddressLatLong(const StreetAddress& refsa, double dLat, double dLong)
{
	m_rgStreetAddress.push_back(refsa);
	m_rgLat.push_back(dLat);
	m_rgLong.push_back(dLong);
}

StreetAddress GeolocationFromFiledata::GetStreetAddressByLatitudeLongitude(double dLat, double dLong)
{
	StreetAddress erg;
	if (m_rgStreetAddress.size() > 0)
	{
		erg = m_rgStreetAddress[0];
		double dBestDistance = sqrt((m_rgLat[0]-dLat) * (m_rgLat[0] - dLat) + (m_rgLong[0] - dLong) * (m_rgLong[0] - dLong));
		for (size_t i = 0; i < m_rgStreetAddress.size(); i++)
		{
			double dDistance = sqrt((m_rgLat[i] - dLat) * (m_rgLat[i] - dLat) + (m_rgLong[i] - dLong) * (m_rgLong[i] - dLong));
			if (dDistance < dBestDistance)
			{
				erg = m_rgStreetAddress[i];
				dBestDistance = dDistance;
			}
		}
	}
	return erg;
}


