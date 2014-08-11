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
#include "boost/format.hpp"					//Purtifying Output
#include "Circleplot.h"

using namespace std;
using namespace GeographicLib;

string Circle::FormatPlacemark()
{
    ostringstream ss;
    ostringstream rr;
    ostringstream tt;
    string combined;


    ss
		<< "<Placemark>\n"
		<< "<name>" << getSpot() << "</name>\n"
		<< "<description>"  << getDesc() << "</description>\n"
		<< "<LineString>\n"
		<< "<coordinates>\n";
    rr
//		<< getLat() << "," << getLon()<< ",0\n";
    	<< createCircle();
	tt
		<< "</coordinates>\n"
		<< "</Linestring>\n"
		<< "</Placemark>\n";

	combined = ss.str()+rr.str()+tt.str();
    return combined;
}

