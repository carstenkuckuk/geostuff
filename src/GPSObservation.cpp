// Project: geostuff
// File: GPSObservation.cpp
//
// Lat+Long+Time
//

#include "GPSObservation.hpp"

#include <cmath>

double DegreesToRadians(double dDegrees)
{
	return dDegrees / 180.0 * pi;
}


double DinstanceInMeters(const GPSObservation &p1, const GPSObservation &p2)
{
	// Altmeister: https://stackoverflow.com/questions/27126714/c-latitude-and-longitude-distance-calculator
	double dLat1InRad = DegreesToRadians(p1.m_dLat);
	double dLong1InRad = DegreesToRadians(p1.m_dLong);
	double dLat2InRad = DegreesToRadians(p2.m_dLat);
	double dLong2InRad = DegreesToRadians(p2.m_dLong);

	double d = 6371.0 * acos(sin(dLat1InRad) * sin(dLat2InRad) + cos(dLat1InRad) * cos(dLat2InRad) * cos(dLong1InRad - dLong2InRad));

	return d * 1000.0;
}

bool GPSObservation::operator==(const GPSObservation &refThat) const
{
	const double dEpsilon = 0.00001;
	const bool bEqual =
		(fabs(m_dVelocity_km_per_hour-refThat.m_dVelocity_km_per_hour)<dEpsilon) &&
		(m_nDateTime==refThat.m_nDateTime) &&
		(fabs(m_dLat - refThat.m_dLat) < dEpsilon) &&
		(fabs(m_dLong - refThat.m_dLong) < dEpsilon) &&
		(fabs(m_dElevationAboveSealevelInMeters - refThat.m_dElevationAboveSealevelInMeters) < dEpsilon);
	return bEqual;
};
