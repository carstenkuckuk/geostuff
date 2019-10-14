// Project: geostuff
// File: GPSTrackfile.cpp
//
// Reads GPSObservation objects from a file or writes GPSObservation objects to a file. The
// file format is a simple CSV file format with four columns: datetime, latitude, longitude, meters above sea-level (if present)
//

#include "GPSTrackFile.hpp"

GPSTrackFile::GPSTrackFile()
	:m_fp(0), m_bOpenedForReading(false), m_bOpenedForWriting(false)
{
}

GPSTrackFile::~GPSTrackFile()
{
	if (m_bOpenedForReading)
	{
		fclose(m_fp);
		m_bOpenedForReading = false;
	}

	if (m_bOpenedForWriting)
	{
		fclose(m_fp);
		m_bOpenedForWriting = false;
	}
}

bool GPSTrackFile::OpenForWrite(const std::string &refstrFileName) // true=success, false=failure
{
	bool bSuccess = false;
	m_strFileName = refstrFileName;
	m_fp = fopen(refstrFileName.c_str(), "w");
	if (m_fp)
	{
		m_bOpenedForWriting = true;
		bSuccess = true;
	}
	else
	{
		m_bOpenedForWriting = false;
		bSuccess = false;
	}
	return bSuccess;
}


bool GPSTrackFile::OpenForRead(const std::string &refstrFileName) // true=success, false=failure
{
	bool bSuccess = false;
	m_strFileName = refstrFileName;
	m_fp = fopen(refstrFileName.c_str(), "r");
	if (m_fp)
	{
		m_bOpenedForReading = true;
		bSuccess = true;
	}
	else
	{
		m_bOpenedForReading = false;
		bSuccess = false;
	}
	return bSuccess;
}


void GPSTrackFile::Close()
{
	if (m_bOpenedForReading)
	{
		fclose(m_fp);
		m_bOpenedForReading = false;
	}

	if (m_bOpenedForWriting)
	{
		fclose(m_fp);
		m_bOpenedForWriting = false;
	}
}

bool GPSTrackFile::ReadGPSObservationFromFile(GPSObservation &refGO) // true=success, false=failure i.e. end of file reached
{
	bool bSuccess = false;
	if (m_bOpenedForReading)
	{
		char buf[200]; buf[0] = 0;
		int nRes=
		fscanf(m_fp, "%d, %lf, %lf, %lf, %lf, %[^\n]\n", 
			&refGO.m_nDateTime, &refGO.m_dLat, &refGO.m_dLong, &refGO.m_dElevationAboveSealevelInMeters,
			&refGO.m_dVelocity_km_per_hour, &buf);
		refGO.m_strComment = buf;
		bSuccess = (nRes==6);
	}

	return bSuccess;
}

bool GPSTrackFile::ReadGPSObservationsFromFile(std::vector<GPSObservation> &refrgObservations) // true=success, false=failure
{
	bool bFileEndReached = false;
	while (!bFileEndReached)
	{
		GPSObservation go;
		bool bSuccess = ReadGPSObservationFromFile(go);
		if (bSuccess)
		{
			refrgObservations.push_back(go);
		}
		else
		{
			bFileEndReached = true;
		}
	}
	return true;
}

bool GPSTrackFile::WriteGPSObservationToFile(const GPSObservation &refGO) // true=success, false: real failure
{
	bool bSuccess = false;
	if (m_bOpenedForWriting)
	{
		fprintf(m_fp, "%d, %lf, %lf, %lf, %lf, %s\n", 
			refGO.m_nDateTime, refGO.m_dLat, refGO.m_dLong, refGO.m_dElevationAboveSealevelInMeters,
			refGO.m_dVelocity_km_per_hour, refGO.m_strComment.c_str()
			);
		bSuccess = true;
	}
	return bSuccess;
}

bool GPSTrackFile::WriteGPSObservationsToFile(const std::vector<GPSObservation> &refrgObservations)  // true=success, false: real failure
{
	bool bErg = true;

	for (auto o : refrgObservations)
	{
		bool bSuccess = WriteGPSObservationToFile(o);
		bErg = bErg && bSuccess;
	}
	return bErg;
}