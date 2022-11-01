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

static const double pi = 3.14159265358979323846;
static double DegreesToRadians(double dDegrees)
{
	return dDegrees / 180.0 * pi;
}

static double ww_distance_in_meters(double dLat1, double dLong1, double dLat2, double dLong2)
{
	// Altmeister: https://stackoverflow.com/questions/27126714/c-latitude-and-longitude-distance-calculator
	double dLat1InRad = DegreesToRadians(dLat1);
	double dLong1InRad = DegreesToRadians(dLong1);
	double dLat2InRad = DegreesToRadians(dLat2);
	double dLong2InRad = DegreesToRadians(dLong2);

	double d = 6371.0 * acos(sin(dLat1InRad) * sin(dLat2InRad) + cos(dLat1InRad) * cos(dLat2InRad) * cos(dLong1InRad - dLong2InRad));

	return d * 1000.0;

}


std::pair<StreetAddress,double> GeolocationFromFiledata::GetStreetAddressByLatitudeLongitude(double dLat, double dLong)
{
	double dBestDistanceInMeters = 9999999;
	StreetAddress erg;
	if (m_rgStreetAddress.size() > 0)
	{
		double dBestLat = m_rgLat[0];
		double dBestLong = m_rgLong[0];
		erg = m_rgStreetAddress[0];
		double dBestDistance = sqrt((m_rgLat[0]-dLat) * (m_rgLat[0] - dLat) + (m_rgLong[0] - dLong) * (m_rgLong[0] - dLong));

		for (size_t i = 0; i < m_rgStreetAddress.size(); i++)
		{
			double dDistance = sqrt((m_rgLat[i] - dLat) * (m_rgLat[i] - dLat) + (m_rgLong[i] - dLong) * (m_rgLong[i] - dLong));
			if (dDistance < dBestDistance)
			{
				dBestLat = m_rgLat[i];
				dBestLong = m_rgLong[i];
				erg = m_rgStreetAddress[i];

				dBestDistance = dDistance;
			}
		}

		dBestDistanceInMeters = ww_distance_in_meters(dLat, dLong, dBestLat, dBestLong);
	}
	return std::pair<StreetAddress, double>(erg, dBestDistanceInMeters);
}


