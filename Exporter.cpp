#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <boost/regex.hpp>					//Boost REGEX
#include <boost/algorithm/string/trim.hpp> 	//Boost Trim
#include <boost/lexical_cast.hpp>			//Converts strings to numbers
#include <stdlib.h>							//For double conversion from string
#include "GeographicLib/UTMUPS.hpp"			//Conversion of MGRS
#include "GeographicLib/MGRS.hpp"			//Conversion of MGRS
#include "GeographicLib/GeoCoords.hpp"      //GeoCoords class
#include "boost/format.hpp"					// Purtifying Output
#include "Circleplot.h"

using namespace std;
using namespace GeographicLib;

string Circle::FormatPlacemark()
{
//	cout << "TEST:: " << description << lat << lon;
    ostringstream ss;

    ss
		<< "<?xml version='1.0' encoding='utf-8'?>\n"
		<< "<kml xmlns='http://www.opengis.net/kml/2.2'>"
		<< "<Placemark>\n"
		<< "<name>" << spot << "</name>\n"
		<< "<description> "  << description << "</description>\n"
		<< "<Point>\n"
		<< "<coordinates>\n"
		<< getCoords().Longitude() << "," << getCoords().Latitude()<< ",0\n"
		<< "</coordinates>\n"
		<< "</Point>\n"
		<< "</Placemark>\n"
		<< "</kml>\n";


    return ss.str();
}

