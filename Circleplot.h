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
    Circle(string spot, string coordinate, double radius, string description);

    // Private Information Grabbers //
    string          getSpot();
    double          getRadius();
    GeoCoords       getCoords();
    string          getDesc();
    double          getRealrad();

    // Information Display //
    void            printValues();
    string          generatePlacemark();
    string          createCircle();

private:
    void            setValues(string newSpot, string newCoords, double newRadius, string newDescription);
    string          spot;
    GeoCoords       coordinate;
    double          radius;
    string          description;
};

// Prototypes //
string              prepKml(vector<Circle> circles);
void                createZip(string filename, vector<Circle> circles);


#endif
