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

string FormatPlacemark(double lat1, double long1, double lat2, double long2)
{


    ostringstream ss;
    ss << "<Placemark>\n"
       << "<name>Path</name>\n"
       << "<description> "  << "</description>\n"
       << "<styleUrl>#pathstyle</styleUrl>\n"
       << "<LineString>\n"
       << "<tessellate>1</tessellate>\n"
       << "<coordinates>"
       << long1 << "," << lat1 << ",0"
       << " "
       << long2 << "," << lat2 << ",0"
       << "</coordinates>\n"
       << "</LineString>\n"
       << "</Placemark>\n";

    return ss.str();
}

int main () {
	ofstream handle;

	// http://www.cplusplus.com/reference/ios/ios/exceptions/
	// Throw an exception on failure to open the file or on a write error.
	handle.exceptions(std::ofstream::failbit | std::ofstream::badbit);

	// Open the KML file for writing:
	handle.open("C:/Output/Sample.kml");

	// Write to the KML file:
	handle << "<?xml version='1.0' encoding='utf-8'?>\n";
	handle << "<kml xmlns='http://www.opengis.net/kml/2.2'>\n";

	handle << FormatPlacemark(-76.2, 38.5, -76.1, 38.6);

	handle << "</kml>\n";
	handle.close();
}


