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
		if (d > 20)
		{
			if ((0 <= v) && (v <= 10))
			{ // Fussgaenger
				m_refRoadmap.AddPointAt(refgpsobservation.m_dLong, refgpsobservation.m_dLat, 1);

			}
			else
				if ((10 <= v) && (v <= 50))
				{// Strasse
					m_refRoadmap.AddPointAt(refgpsobservation.m_dLong, refgpsobservation.m_dLat, 2);

				}
				else
				{//Autobahn
					m_refRoadmap.AddPointAt(refgpsobservation.m_dLong, refgpsobservation.m_dLat, 3);

				}

			m_LastObservation = refgpsobservation;
		}

}
