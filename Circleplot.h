#ifndef _CIRCLEPLOT_H
#define _CIRCLEPLOT_H

#include <iostream>
#include <string>
#include "GeographicLib/UTMUPS.hpp"
#include "GeographicLib/MGRS.hpp"
#include "GeographicLib/GeoCoords.hpp"
using namespace std;
using namespace GeographicLib;

struct Circle {
public:
    // Constructors //
    Circle() {}
    Circle(const string &line);

    // Private Information Grabbers //
    string          getSpot();
    double          getRadius(string);
    GeoCoords       getCoords();
    string          getDesc();
    double          getRealrad();

    // Information Display //
    void            printValues();
    string          FormatPlacemark();
    string          createCircle();

private:
    void            setValues(string spot, string coords, string radius, string description);
    string          spot;
    GeoCoords       coords;
    double          radius;
    string          description;
};

// Prototypes //
GeoCoords           getCoords();
double              getRadius(string);
double              getRealrad();
string              createCircle();
vector<string>      split(const string& s, char c);
string              prepKml();

#endif
