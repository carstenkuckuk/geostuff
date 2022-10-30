// Project: geostuff
// File: StreetAddress.hpp
//
// Street Address. Used in Geolocation API
//

#ifndef __GEOSTUFF_STREETADDRESS_HPP__
#define __GEOSTUFF_STREETADDRESS_HPP__

#include <string>

// All members modelled as strings in order to allow for local specific variations. This class is 
// only intended for interfacing to humans, not for computations or such

class StreetAddress
{
public:
	std::string m_strCountryCode;	// "DE"
	std::string m_strZip;
	std::string m_strCity;
	std::string m_strStreetname;
	std::string m_strStreetnumber; 
	std::string m_strDescription; // for example: Restaurant Havelli
};

std::string toString(const StreetAddress& refsa);

#endif
