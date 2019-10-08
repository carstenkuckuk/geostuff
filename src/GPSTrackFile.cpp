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
		int nRes=
		fscanf(m_fp, "%lf, %lf, %lf\n", &refGO.m_dLat, &refGO.m_dLong, &refGO.m_dElevationAboveSealevelInMeters);
		bSuccess = (nRes==3);
	}

	return bSuccess;
}

bool GPSTrackFile::WriteGPSObservationToFile(const GPSObservation &refGO) // true=success, false: real failure
{
	bool bSuccess = false;
	if (m_bOpenedForWriting)
	{
		fprintf(m_fp, "%lf, %lf, %lf\n", refGO.m_dLat, refGO.m_dLong, refGO.m_dElevationAboveSealevelInMeters);
		bSuccess = true;
	}
	return bSuccess;
}
