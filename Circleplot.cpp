#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <pcrecpp.h>
#include <fstream>

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
//----------------------------//

void Circle::setValues(string newSpot, string newCoords, double newRadius, string newDescription)
{
    GeoCoords   c(newCoords);
    spot        = newSpot;
    coordinate  = c;
    radius      = newRadius;
    description = newDescription;
}

string Circle::getSpot() {
    return spot;
}
double Circle::getRadius() {
    return radius;
}
GeoCoords Circle::getCoords() {
    return coordinate;
}
string Circle::getDesc() {
    return description;
}

Circle::Circle(string spot, string coordinate, double radius, string description)
{
    setValues(spot, coordinate, radius, description);
}


  //---------------------------------------------------------------------------------------------------------------------------------------------//
 // File Handlers //
//---------------//

Circle parseLine(const string line) {
    string spot;
    string coordinate;
    double radius;
    string unit;
    string description;
    pcrecpp::RE regex(R"!(^(.+?),(.+?),\s*([\d\.]+)(KM|M),\s*"(.+)")!");
    if (!regex.PartialMatch(line, &spot, &coordinate, &radius, &unit, &description)) {
        cout << "Could not parse ->" << line << "<-" << endl;
        throw string("Error");
    }
    if (unit == "M") {
        radius *= 1;
    }
    else if (unit == "KM") {
        radius *= 1000;
    }
    else {
        throw string("Unknown unit: ") + unit;
    }
//    double convRadius = (double) radius;
    return Circle(spot, coordinate, radius, description);
}

vector<Circle> processFile(string filename) {
    string line;
    ifstream file(filename);
    stringstream out;
    vector<Circle> fileLines;

    while (std::getline(file, line)) {
        if (!file.eof())
        {
            fileLines.push_back(parseLine(line));
        }
    }
    return fileLines;
}

void Circle::printValues()
{
    cout << getSpot() << endl;
    cout << getRadius() << endl;
    cout << getCoords().MGRSRepresentation() << endl;
    cout << getDesc() << endl;
}


  //---------------------------------------------------------------------------------------------------------------------------------------------//
 // Main Application //
//------------------//

int main(int argc, char *argv[])
{
    if (argc >= 3 || argc <= 1)
    {
        cout << "Invalid Arguments. Please provide a filename only." << endl;
        return 0;
    }
    string filename = argv[1];
    vector<Circle> circles;
    circles = processFile(filename);
    int i;
    for (i = 0; i < circles.size(); i++)
    {
        circles[i].printValues();
    }

}


