// Project: geostuff
// File: GPSObservation.hpp
//
// Lat+Long+Time
//
#ifndef __GEOSTUFF_GPSOBSERVATION_HPP__
#define __GEOSTUFF_GPSOBSERVATION_HPP__

#include <string>

static const double pi = 3.14159265358979323846;

class GPSObservation
{
public:
	GPSObservation(__int64 nDateTime=0, double dLat=0.0, double dLong=0.0, double dElevationAboveSealevelInMeters=0.0, double dVelocity_km_per_hour=0.0, std::string strComment="x")
		:m_nDateTime(nDateTime), m_dLat(dLat), m_dLong(dLong), 
		m_dElevationAboveSealevelInMeters(dElevationAboveSealevelInMeters),
	m_dVelocity_km_per_hour(dVelocity_km_per_hour), m_strComment(strComment)
	{};
	bool operator==(const GPSObservation &refThat) const;

	__int64 m_nDateTime; // WigleWife Date Time Format: time_t, aber mit 1000 multipliziert....
	double m_dLat; // degrees
	double m_dLong; // degrees
	double m_dElevationAboveSealevelInMeters;
	double m_dVelocity_km_per_hour;
	std::string m_strComment;
};

double DegreesToRadians(double dDegrees);
double DinstanceInMeters(const GPSObservation &p1, const GPSObservation &p2);
std::string DateTimeToString(__int64 nDateTime);

#endif
