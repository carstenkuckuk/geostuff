// Project: geostuff
// File: MapBuilder.cpp
//
// Contains the analysis logic that analyzes GPS Tracks and tries to create a map from it or improve an existing one
//

#include "Mapbuilder.hpp"

#include "Roadmap.hpp"
#include "GPSObservation.hpp"

MapBuilder::MapBuilder(Roadmap& refRoadmap)
	:m_refRoadmap(refRoadmap)
{
}

MapBuilder::~MapBuilder()
{
}

void MapBuilder::FeedGPSObservation(GPSObservation& refgpsobservation)
{
		double d = DinstanceInMeters(m_LastObservation, refgpsobservation);
		double dinkm = d / 1000;
		double dTime = refgpsobservation.m_nDateTime - m_LastObservation.m_nDateTime; // in millisekunden
		double dTimeinH = dTime / 1000.0 / 60.0 / 60.0;;
		double v = dinkm / dTimeinH;

		int nIndex1 = m_refRoadmap.FindOrCreateRoadmapPointByLongLat(m_LastObservation.m_dLong, m_LastObservation.m_dLat);
		int nIndex2 = m_refRoadmap.FindOrCreateRoadmapPointByLongLat(refgpsobservation.m_dLong, refgpsobservation.m_dLat);
		m_refRoadmap.AddConnectionIfNotExists(nIndex1, nIndex2, v);

		m_LastObservation = refgpsobservation;

}
