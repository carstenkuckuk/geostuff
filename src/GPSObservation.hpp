// Project: geostuff
// File: GPSObservation.hpp
//
// Lat+Long+Time
//
#ifndef __GEOSTUFF_GPSOBSERVATION_HPP__
#define __GEOSTUFF_GPSOBSERVATION_HPP__

static const double pi = 3.14159265358979323846;

class GPSObservation
{
public:
	GPSObservation(double dLat=0.0, double dLong=0.0) :m_dLat(dLat), m_dLong(dLong) {};

	double m_dLat; // degrees
	double m_dLong; // degrees
};

double DegreesToRadians(double dDegrees);
double DinstanceInMeters(const GPSObservation &p1, const GPSObservation &p2);

#endif
