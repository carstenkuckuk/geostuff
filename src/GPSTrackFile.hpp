// Project: geostuff
// File: GPSTrackfile.hpp
//
// Reads GPSObservation objects from a file or writes GPSObservation objects to a file. The
// file format is a simple CSV file format with four columns: datetime, latitude, longitude, meters above sea-level (if present)
//
#ifndef __GEOSTUFF_GPSTRACKFILE_HPP__
#define __GEOSTUFF_GPSTRACKFILE_HPP__

#include "GPSObservation.hpp"
#include <string>
#include <vector>
// Fuer den FILE-Pointer:
#include <stdio.h>

class GPSTrackFile
{
public:
	GPSTrackFile();
	virtual ~GPSTrackFile();

	virtual bool OpenForWrite(const std::string &refstrFileName); // true=success, false=failure
	virtual bool OpenForRead(const std::string &refstrFileName); // true=success, false=failure
	virtual void Close();

	virtual bool ReadGPSObservationFromFile(GPSObservation &refGO); // true=success, false=failure i.e. end of file reached
	virtual bool WriteGPSObservationToFile(const GPSObservation &refGO); // true=success, false: real failure
	virtual bool WriteGPSObservationsToFile(const std::vector<GPSObservation> &refrgObservations);  // true=success, false: real failure

	std::string m_strFileName;
	FILE *m_fp;
	bool m_bOpenedForReading;
	bool m_bOpenedForWriting;
};


#endif
