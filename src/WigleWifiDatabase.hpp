// Datei WigleWifiDatabase.hpp
//
// Klasse, die eine WigleWifi SQLite Datenbank öffnen und daraus lesen kann

#ifndef __GEOSTUFF_WIGLEWIFIDATABASE_HPP__
#define __GEOSTUFF_WIGLEWIFIDATABASE_HPP__

#include <string>
#include <vector>
#include "GPSObservation.hpp"


struct sqlite3;

class WigleWifiDatabase
{
public:
	WigleWifiDatabase();
	virtual ~WigleWifiDatabase();

	virtual bool Open(std::string strDateiname);
	virtual bool Close();

	virtual void ReadAllGPSObservations(std::vector<GPSObservation>  &refrgGPSObservations);
	sqlite3 *m_pDB;
};

#endif

