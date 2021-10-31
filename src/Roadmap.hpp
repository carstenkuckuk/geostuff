// Project: geostuff
// File: Roadmap.hpp
//
// Represents a map of Roads. A Roadmap consists of Points, and directed connections between these points. These connections contain information about the speed
// that they were traversed, and the number of times they got traversed. The points also contain the number of times they got frequented. 
// Reasoning:
// Points and Connections is the real map data. As we work from GPS tracking information, we can only determine the average speed of a road and try to guess if they are roads or footpaths from the speed information
// The frequency information is stored so that we know how much we can change this information when we add new tracking information. 
//

#ifndef __GEOSTUFF_ROADMAP_HPP__
#define __GEOSTUFF_ROADMAP_HPP__

#include <string>
#include <vector>

class RoadmapPoint
{
public:
	RoadmapPoint();
	virtual ~RoadmapPoint();

	size_t m_nPK;
	double m_dLong;
	double m_dLat;
	size_t m_nWeight;
};

class RoadmapConnection
{
public:
	RoadmapConnection();
	virtual ~RoadmapConnection();

	size_t m_nPK;
	size_t m_nFromPointID;
	size_t m_nToPointID;
	size_t m_nWeight;
	double m_nMinimumVelocityObserved;
	double m_nMaximumVelocityObserved;
	double m_nSumOfVelocitiesObserved; // Mittlere Geschwindigkeit ist dann Summe durch Anzahl

};

class Roadmap
{
public:
	Roadmap();
	virtual ~Roadmap();

	size_t FindOrCreateRoadmapPointByLongLat(double dLong, double dLat, double dEpsilon=0.0001);
	size_t AddConnectionIfNotExists(size_t nIndexPoint1, size_t nIndexPoint2, double dVelocity);

	std::vector<RoadmapPoint> m_rgRoadmapPoints;
	std::vector<RoadmapConnection> m_rgRoadmapConnections;

};

void ReadRoadmapFromFile(Roadmap& refRoadmap, const std::string& refstrFilename);
void WriteRoadmapToFile(const Roadmap& refRoadmap, const std::string& refstrFilename);

#endif
