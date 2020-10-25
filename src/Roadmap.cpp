// Project: geostuff
// File: Roadmap.cpp
//
// Represents a map of Roads. A Roadmap consists of Points, and directed connections between these points. These connections contain information about the speed
// that they were traversed, and the number of times they got traversed. The points also contain the number of times they got frequented. 
// Reasoning:
// Points and Connections is the real map data. As we work from GPS tracking information, we can only determine the average speed of a road and try to guess if they are roads or footpaths from the speed information
// The frequency information is stored so that we know how much we can change this information when we add new tracking information. 
//

#include "Roadmap.hpp"

#include <stdio.h>

Roadmap::Roadmap()
{
}

Roadmap::~Roadmap()
{
}


void Roadmap::AddPointAt(double dLong, double dLat, int nType)
{
	m_rgLong.push_back(dLong);
	m_rgLat.push_back(dLat);
	m_rgType.push_back(nType);
}




void ReadRoadmapFromFile(Roadmap& refRoadmap, const std::string& refstrFilename)
{
	FILE* fp = fopen(refstrFilename.c_str(), "r");

	bool bMoreToRead = (fp != 0);
	while (bMoreToRead)
	{
		double dLong = 0.0;
		double dLat = 0.0;
		int nType = 0;
		char buf[200]; buf[0] = 0;
		int nRes = fscanf(fp, "%lf,%lf,%d,%[^\n]\n", &dLong, &dLat, &nType, &buf);
		
		if (nRes == 3)
		{
			refRoadmap.m_rgLong.push_back(dLong);
			refRoadmap.m_rgLat.push_back(dLat);
			refRoadmap.m_rgType.push_back(nType);
		}
		else
		{
			bMoreToRead = false;
		}
	}
	if (fp)
	{
		fclose(fp);
	}
}

void WriteRoadmapToFile(const Roadmap& refRoadmap, const std::string& refstrFilename)
{
	FILE* fp = fopen(refstrFilename.c_str(), "w");

	if (fp)
	{
		size_t nAnz = refRoadmap.m_rgLong.size();
		for (size_t i = 0; i < nAnz; i++)
		{
			double dLong = refRoadmap.m_rgLong[i];
			double dLat  = refRoadmap.m_rgLat[i];
			int nType = refRoadmap.m_rgType[i];

			fprintf(fp, "%lf,%lf,%d,\n", dLong, dLat, nType);
		}

		fclose(fp);
	}

}
