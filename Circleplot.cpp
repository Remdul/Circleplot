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
    return Circle(spot, coordinate, radius, description);
}

vector<Circle> processFile(string filename) {
    string line;
    ifstream file(filename);
    stringstream out;
    vector<Circle> fileLines;

    while (std::getline(file, line)) {
        if (line != "")
       // if (!file.eof())
        {
            cout << line << endl;
            fileLines.push_back(parseLine(line));
        }
    }
    return fileLines;
}

  //---------------------------------------------------------------------------------------------------------------------------------------------//
 // Displaying Information //
//------------------------//

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
bool mainMenu(string filename, vector<Circle> circles)
{
    int selection;
    string zipName;
    string kmlName;
    ofstream handle;

    cout << "Main Menu:" << endl;
    cout << "----------" << endl;
    cout << "File Chosen: " << filename << endl << endl;
    cout << "What would you like to do?" << endl;
    cout << "1) Create KML file." << endl;
    cout << "2) Create KMZ file." << endl;
    cout << "3) Print Data to Screen." << endl;
    cout << "0) Quit." << endl;

    cin >> selection;
    switch (selection)
    {
        case 1:
            cout << "Creating KML File." << endl;

            cout << "Name the file: " << endl;
            cin >> kmlName;
// TROUBLESHOOTING
//            handle.exceptions(std::ofstream::failbit | std::ofstream::badbit);
//            const char * kmlFilename = kmlName.c_str();
//            handle.open(kmlFilename);
//            handle << prepKml(circles);
//            handle.close();

            return false;
        case 2:
            cout << "Name the file: " << endl;
            cin >> zipName;
            cout << "Creating KMZ File." << endl;
            createZip(zipName, circles);
            return false;
        case 3:
            cout << "Here you go!" << endl;
            for (int i = 0; i < circles.size(); i++)
            {
                circles[i].printValues();
            }

            return false;
        case 0:
            return true;
    }
}

int main(int argc, char *argv[])
{
    bool quit = false;
    if (argc >= 3 || argc <= 1)
    {
        cout << "Invalid Arguments. Please provide a filename only." << endl;
        return 0;
    }
    string filename = argv[1];
    vector<Circle> circles;
    circles = processFile(filename);

    while (quit == false)
    {
        quit = mainMenu(filename, circles);
    }
}


