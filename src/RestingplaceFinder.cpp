// Project: geostuff
// File: RestingplaceFinder.cpp
//
// Takes observations of a GPS track and tries to determine where the subject rested for a longer time
//

#include "RestingplaceFinder.hpp"

#include "GPSObservation.hpp"


double ww_delta_t_in_seconds(__int64 nwwtm1, __int64 nwwtm2) // WigleWifi time_tm is scaled by 1000.0
{
	double dtm1 = nwwtm1 / 1000.0;
	double dtm2 = nwwtm2 / 1000.0;
	double delta_t_in_seconds = dtm2 - dtm1;
	return delta_t_in_seconds;
}

static double DegreesToRadians(double dDegrees)
{
	return dDegrees / 180.0 * pi;
}

double ww_distance_in_meters(double dLat1, double dLong1, double dLat2, double dLong2)
{
	// Altmeister: https://stackoverflow.com/questions/27126714/c-latitude-and-longitude-distance-calculator
	double dLat1InRad = DegreesToRadians(dLat1);
	double dLong1InRad = DegreesToRadians(dLong1);
	double dLat2InRad = DegreesToRadians(dLat2);
	double dLong2InRad = DegreesToRadians(dLong2);

	double d = 6371.0 * acos(sin(dLat1InRad) * sin(dLat2InRad) + cos(dLat1InRad) * cos(dLat2InRad) * cos(dLong1InRad - dLong2InRad));

	return d * 1000.0;

}

double ww_velocity_im_km_per_hour(double dLat1, double dLong1, __int64 nwwtm1, double dLat2, double dLong2, __int64 nwwtm2)
{
	double delta_t_in_seconds = ww_delta_t_in_seconds(nwwtm1, nwwtm2);
	double delta_t_in_minutes = delta_t_in_seconds / 60.0;
	double delta_t_in_hours = delta_t_in_minutes / 60.0;

	double distance_in_meters = ww_distance_in_meters(dLat1, dLong1, dLat2, dLong2);
	double dinstance_in_kilometers = distance_in_meters / 1000.0;

	double velocity_in_km_per_hour = dinstance_in_kilometers / delta_t_in_hours;

	return velocity_in_km_per_hour;
}


Hypothese::Hypothese()
:m_bGenugZeitZusammenFuerAufenthaltsort(false),
		m_nwwtmStartzeit(0), m_dStartLat(0.0), m_dStartLong(0.0),
		m_nwwtmLetztezeit(0), m_dLetzteLat(0.0), m_dLetzteLong(0)
{
}

bool Hypothese::ZeitsprungZuGross(__int64 nwwtm) // true, wenn mehr als zwei Minuten zwischen den Observationen vergangen sind
{
	double delta_t_seconds = ww_delta_t_in_seconds(m_nwwtmLetztezeit, nwwtm);
	bool bErg = delta_t_seconds > 2 * 60; // mehr als 2 Minuten
	return bErg;
}

bool Hypothese::GeschwindigkeitZuGross(double dLat, double dLong, __int64 nwwtm) // true, wenn man sich schneller als 6 km/h bewegt hat
{
	double velocity_km_per_hour = ww_velocity_im_km_per_hour(m_dLetzteLat, m_dLetzteLong, m_nwwtmLetztezeit, dLat, dLong, nwwtm);
	bool bErg = velocity_km_per_hour > 6.0;
	return bErg;
}

bool Hypothese::DistanzZuGross(double dLat, double dLong) // true, wenn man sich mehr als 50m vom Ort wegbewegt hat
{
	double distance_in_meters = ww_distance_in_meters(m_dStartLat, m_dStartLong, dLat, dLong);
	bool bErg = distance_in_meters > 50.0;
	return bErg;
}

bool Hypothese::ZeitAusreichendFuerAufenthaltsort(__int64 nwwtm) // true, wenn wir mindestens 15 Minuten zusammen haben
{
	double delta_t_seconds = ww_delta_t_in_seconds(m_nwwtmStartzeit, nwwtm);
	bool bErg = delta_t_seconds > 15 * 60; // mehr als 15 Minuten
	return bErg;

}

void Hypothese::SetzeNeuenLetztenPunkt(double dLat, double dLong, __int64 nwwtm) // Aufrufen, wenn ein neuer Punkt zur Hypothese paßt
{
	m_dLetzteLat = dLat;
	m_dLetzteLong = dLong;
	m_nwwtmLetztezeit = nwwtm;
}

void Hypothese::BeginneMitNeuerHypotheseAb(double dLat, double dLong, __int64 nwwtm)
{
	m_bGenugZeitZusammenFuerAufenthaltsort = false;
	
	m_nwwtmStartzeit = nwwtm;
	m_dStartLat = dLat;
	m_dStartLong = dLong;

	m_nwwtmLetztezeit = nwwtm;
	m_dLetzteLat = dLat;
	m_dLetzteLong = dLong;
}











RestingplaceFinder::RestingplaceFinder()
{
}

RestingplaceFinder::~RestingplaceFinder()
{
}

void RestingplaceFinder::ProcessGPSObservation(const GPSObservation& refgo)
{
	if (refgo.m_nDateTime == m_h.m_nwwtmLetztezeit)
		return; // Keine Zeit vergangen: NOP
	
	if (
		m_h.ZeitsprungZuGross(refgo.m_nDateTime) ||
		m_h.GeschwindigkeitZuGross(refgo.m_dLat, refgo.m_dLong, refgo.m_nDateTime) ||
		m_h.DistanzZuGross(refgo.m_dLat, refgo.m_dLong)
		)
	{
		// Altes Segment ist zu Ende und ein neues muß begonnen werden. Wenn altes eine erfolgreiche Erkennung war, dann merken wir sie uns:
		if (m_h.m_bGenugZeitZusammenFuerAufenthaltsort)
		{
			Restingplace rp(m_h.m_dStartLat, m_h.m_dStartLong);
			m_rgRestingplaces.push_back(rp);
		}
		// Neues Segment beginnen:
		m_h.BeginneMitNeuerHypotheseAb(refgo.m_dLat, refgo.m_dLong, refgo.m_nDateTime);
	}
	else
	{
		// Altes Segment wird fortgeführt mit diesem neuen Punkt:
		m_h.SetzeNeuenLetztenPunkt(refgo.m_dLat, refgo.m_dLong, refgo.m_nDateTime);
		if (m_h.ZeitAusreichendFuerAufenthaltsort(refgo.m_nDateTime))
		{
			m_h.m_bGenugZeitZusammenFuerAufenthaltsort = true;
		}
	}

}

std::vector<Restingplace> RestingplaceFinder::GetRestingplaces()
{
	return m_rgRestingplaces;
}
