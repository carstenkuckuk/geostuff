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


RoadmapPoint::RoadmapPoint()
:m_nPK(0), m_dLong(0.0), m_dLat(0.0), m_nWeight(0)
{
}

RoadmapPoint::~RoadmapPoint()
{
}

RoadmapConnection::RoadmapConnection()
:m_nPK(0), m_nFromPointID(0), m_nToPointID(0), m_nWeight(0),
m_nMinimumVelocityObserved(0.0), m_nMaximumVelocityObserved(0.0), m_nSumOfVelocitiesObserved(0.0)
{
}

RoadmapConnection::~RoadmapConnection()
{

}

Roadmap::Roadmap()
{
}

Roadmap::~Roadmap()
{
}


#if 0
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
#endif

void WriteRoadmapToFile(const Roadmap& refRoadmap, const std::string& refstrFilename)
{
	FILE* fp = fopen(refstrFilename.c_str(), "w");

	if (fp)
	{
		fprintf(fp, "%d,\n", (int)refRoadmap.m_rgRoadmapPoints.size());
		for(auto &refrmp : refRoadmap.m_rgRoadmapPoints)
		{
			int nPK = refrmp.m_nPK;
			double dLong = refrmp.m_dLong;
			double dLat  = refrmp.m_dLat;
			int nWeight = refrmp.m_nWeight;

			fprintf(fp, "%d,%lf,%lf,%d,\n", nPK,dLong, dLat, nWeight);
		}

		fprintf(fp, "%d,\n", (int)refRoadmap.m_rgRoadmapConnections.size());
		for (auto& refrmc : refRoadmap.m_rgRoadmapConnections)
		{
			int nPK = refrmc.m_nPK;
			int nFromPointID = refrmc.m_nFromPointID;
			int nToPointID = refrmc.m_nToPointID;
			int nWeight = refrmc.m_nWeight;
			double nMinimumVelocityObserved = refrmc.m_nMinimumVelocityObserved;
			double nMaximumVelocityObserved = refrmc.m_nMaximumVelocityObserved;
			double nSumOfVelocitiesObserved = refrmc.m_nSumOfVelocitiesObserved; // Mittlere Geschwindigkeit ist dann Summe durch Anzahl

			fprintf(fp, "%d,%d,%d,%d,%lf,%lf,%lf,\n", nPK, nFromPointID, nToPointID, nWeight, nMinimumVelocityObserved, nMaximumVelocityObserved, nSumOfVelocitiesObserved);
		}



		fclose(fp);
	}

}
