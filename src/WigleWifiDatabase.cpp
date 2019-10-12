// Datei WigleWifiDatabase.cpp
//
// Klasse, die eine WigleWifi SQLite Datenbank öffnen und daraus lesen kann

#include "WigleWifiDatabase.hpp"
#include "sqlite3.h"


WigleWifiDatabase::WigleWifiDatabase()
	:m_pDB(0)
{
}

WigleWifiDatabase::~WigleWifiDatabase() 
{
}

bool WigleWifiDatabase::Open(std::string strDateiname)
{
	int nErg = sqlite3_open_v2(strDateiname.c_str(), &m_pDB, SQLITE_OPEN_READONLY, 0);
	return nErg==SQLITE_OK;
}

bool WigleWifiDatabase::Close()
{
	int nErg = sqlite3_close(m_pDB);
	return nErg==SQLITE_OK;
}

void WigleWifiDatabase::ReadAllGPSObservations(std::vector<GPSObservation>  &refrgGPSObservations)
{
	// "select time, lat, lon, altitude from location;"
	std::string strSQL = "select time, lat, lon, altitude from location";
	sqlite3_stmt *pStmt = 0;
	const char *pszTail = 0;

	int nErgPrepare = sqlite3_prepare_v2(m_pDB, strSQL.c_str(), strSQL.size(), &pStmt, &pszTail);
	if (nErgPrepare == SQLITE_OK)
	{
		int nErgStep = 0;
		while (nErgStep = sqlite3_step(pStmt) == SQLITE_ROW)
		{	
			sqlite3_int64 nTime = sqlite3_column_int64(pStmt, 0);
			double dLat = sqlite3_column_double(pStmt, 1);
			double dLon = sqlite3_column_double(pStmt, 2);
			double dAlt = sqlite3_column_double(pStmt, 3);

			GPSObservation go;
			go.m_dLat = dLat;
			go.m_dLong = dLon;
			go.m_dElevationAboveSealevelInMeters = dAlt;
			go.m_nDateTime = nTime;
			go.m_dVelocity_km_per_hour = 0.0; // TO DO: Berechnen!!!!!!!
			refrgGPSObservations.push_back(go);
		}

		sqlite3_finalize(pStmt);
	}

}