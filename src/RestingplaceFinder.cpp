// Project: geostuff
// File: RestingplaceFinder.cpp
//
// Takes observations of a GPS track and tries to determine where the subject rested for a longer time
//

#include "RestingplaceFinder.hpp"

#include "GPSObservation.hpp"

RestingplaceFinder::RestingplaceFinder()
{
}

RestingplaceFinder::~RestingplaceFinder()
{
}

void RestingplaceFinder::ProcessGPSObservation(const GPSObservation& refgo)
{
	if (m_rgRestingplaces.size() < 2)
	{
		Restingplace rp(refgo.m_dLat, refgo.m_dLong);
		m_rgRestingplaces.push_back(rp);
	}
}

std::vector<Restingplace> RestingplaceFinder::GetRestingplaces()
{
	return m_rgRestingplaces;
}
