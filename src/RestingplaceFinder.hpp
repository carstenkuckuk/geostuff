// Project: geostuff
// File: RestingplaceFinder.hpp
//
// Takes observations of a GPS track and tries to determine where the subject rested for a longer time
//
#ifndef __GEOSTUFF_RESTINGPLACEFINDER_HPP__
#define __GEOSTUFF_RESTINGPLACEFINDER_HPP__

#include <vector>

class GPSObservation;

class Restingplace
{
public:
	Restingplace(double dLat = 0.0, double dLong = 0.0) { m_dLat = dLat; m_dLong = dLong; };
	void SetLatLong(double dLat, double dLong) { m_dLat = dLat; m_dLong = dLong; };
	double GetLat() { return m_dLat; };
	double GetLong() { return m_dLong; };
protected:
	double m_dLat;
	double m_dLong;
//	__int64 m_nwwtmFrom; // WigleWife Date Time Format: time_t, aber mit 1000 multipliziert....
//	__int64 m_nwwtmTo;   // WigleWife Date Time Format: time_t, aber mit 1000 multipliziert....
};

class Hypothese
{
public:
	Hypothese();
	bool m_bGenugZeitZusammenFuerAufenthaltsort;

	__int64 m_nwwtmStartzeit;
	double m_dStartLat;
	double m_dStartLong;

	__int64 m_nwwtmLetztezeit;
	double m_dLetzteLat;
	double m_dLetzteLong;

	bool ZeitsprungZuGross(__int64 nwwtm); // true, wenn mehr als zwei Minuten zwischen den Observationen vergangen sind
	bool GeschwindigkeitZuGross(double dLat, double dLong, __int64 nwwtm); // true, wenn man sich schneller als 6 km/h bewegt hat
	bool DistanzZuGross(double dLat, double dLong); // true, wenn man sich mehr als 50m vom Ort wegbewegt hat
	bool ZeitAusreichendFuerAufenthaltsort(__int64 nwwtm); // true, wenn wir mindestens 15 Minuten zusammen haben

	void SetzeNeuenLetztenPunkt(double dLat, double dLong, __int64 nwwtm); // Aufrufen, wenn ein neuer Punkt zur Hypothese pa�t
	void BeginneMitNeuerHypotheseAb(double dLat, double dLong, __int64 nwwtm);
};

class RestingplaceFinder
{
public:
	RestingplaceFinder();
	virtual ~RestingplaceFinder();

	void ProcessGPSObservation(const GPSObservation& refgo);
	std::vector<Restingplace> GetRestingplaces();
protected:
	std::vector<Restingplace> m_rgRestingplaces;

	Hypothese m_h;
};

#endif

