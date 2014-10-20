#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

#include "libzip/lib/zip.h"
#include "GeographicLib/UTMUPS.hpp"			//Conversion of MGRS
#include "GeographicLib/MGRS.hpp"			//Conversion of MGRS
#include "GeographicLib/GeoCoords.hpp"      //GeoCoords class
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Constants.hpp>

#include "Circleplot.h"
#include "Exporter.h"
#include "Utility.h"

using namespace std;
using namespace GeographicLib;

//---------------------------------------------------------------------------------------------------------------------------------------------//
// Class Information Handlers //
//---------------------------//

void Circle::setValues(string newSpot, string newCoords, string newRadius, string newDescription)
{
    GeoCoords   c(newCoords);
    spot        = newSpot;
    coords      = c;
    radius      = getRadius(newRadius);
    description = newDescription;
}

string Circle::getSpot() {return spot;}

double Circle::getRadius(string radius) {
    radius      = trim(radius);
    regex       radsearch("([0-9.\\s]*)([a-zA-Z]*)", std::regex_constants::basic);
    smatch      match;
    cout << radius << endl;
    regex_match(radius, match, radsearch);
    double convertedRad = stringToDouble(match[0]);
    cout << convertedRad << match[0] << match[1];






}
GeoCoords getCoords();
string getDesc();
double getLon();
double getLat();
double getRealrad();

int main()
{
    Circle cir;

    cir.getRadius("2000km");
}


