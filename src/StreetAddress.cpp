// Project: geostuff
// File: StreetAddress.cpp
//
// Street Address. Used in Geolocation API
//

#include "StreetAddress.hpp"

std::string toString(const StreetAddress& refsa)
{
	std::string strErg =
		refsa.m_strDescription + " " +
		refsa.m_strCountryCode + " " + 
		refsa.m_strZip + " " + 
		refsa.m_strCity + " " + 
		refsa.m_strStreetname + " " + 
		refsa.m_strStreetnumber;

	return strErg;
}
