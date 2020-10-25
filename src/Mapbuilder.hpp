// Project: geostuff
// File: MapBuilder.hpp
//
// Contains the analysis logic that analyzes GPS Tracks and tries to create a map from it or improve an existing one
//

#ifndef __GEOSTUFF_MAPBUILDER_HPP__
#define __GEOSTUFF_MAPBUILDER_HPP__

#include "GPSObservation.hpp"

#include <string>
#include <vector>

class Roadmap;
class GPSObservation;

class MapBuilder
{
public:
	MapBuilder(Roadmap &refRoadmap);
	virtual ~MapBuilder();

	void FeedGPSObservation(GPSObservation& refgpsobservation);
protected:

	Roadmap& m_refRoadmap;

	GPSObservation m_LastObservation;

};

#endif
