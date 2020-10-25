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

class Roadmap
{
public:
	Roadmap();
	virtual ~Roadmap();

	virtual void AddPointAt(double dLong, double dLat, int nType);

	std::vector<double> m_rgLong;
	std::vector<double> m_rgLat;
	std::vector<double> m_rgType;

};

void ReadRoadmapFromFile(Roadmap& refRoadmap, const std::string& refstrFilename);
void WriteRoadmapToFile(const Roadmap& refRoadmap, const std::string& refstrFilename);

#endif
