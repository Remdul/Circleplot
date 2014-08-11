#ifndef _CIRCLEPLOT_H
#define _CIRCLEPLOT_H

#include <iostream>
#include <string>
#include "GeographicLib/UTMUPS.hpp"			//Conversion of MGRS
#include "GeographicLib/MGRS.hpp"			//Conversion of MGRS
#include "GeographicLib/GeoCoords.hpp"      //GeoCoords class

using namespace std;
using namespace GeographicLib;


struct Circle {
public:
	string getSpot();
	double getRadius(string);
	GeoCoords getCoords();
	string getDesc();
	void setValues(string, string, string, string);
	void printValues();
	string FormatPlacemark();
	double getLon();
	double getLat();
	double getRealrad();
	string createCircle();
private:
	string 		spot;
	GeoCoords 	coords;
	double 		radius;
	string 		description;
	double		lat;
	double		lon;
};

// PROTOTYPES
GeoCoords 	getCoords();
double		getRadius(string);
double		getRealrad();
double 		getLon();
double 		getLat();
string 		createCircle();


#endif
