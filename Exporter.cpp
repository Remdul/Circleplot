#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include "GeographicLib/UTMUPS.hpp"			//Conversion of MGRS
#include "GeographicLib/MGRS.hpp"			//Conversion of MGRS
#include "GeographicLib/GeoCoords.hpp"      //GeoCoords class
#include <GeographicLib/Geodesic.hpp>

#include "libzip/lib/zip.h"
#include "Circleplot.h"

using namespace std;
using namespace GeographicLib;

string prepKml(vector<Circle> circles)
{
    ostringstream stream;

    stream << "<?xml version='1.0' encoding='utf-8'?>\n";
    stream << "<kml xmlns='http://www.opengis.net/kml/2.2'>\n";
    stream << "<Document>\n";
    for (int i = 0; i < circles.size(); i++){
        stream << circles[i].generatePlacemark();
    }
    stream << "</Document>\n";
    stream << "</kml>\n";
    return stream.str();
}

string Circle::generatePlacemark()
{
    ostringstream ss;
    ostringstream rr;
    ostringstream tt;
    string combined;

    ss
		<< "<Placemark>\n"
		<< "<name>" 		<< spot         << "</name>\n"
		<< "<description>"  << description  << "</description>\n"
		<< "<LineString>\n"
		<< "<coordinates>\n";
    rr
    	<< createCircle();
	tt
		<< "</coordinates>\n"
		<< "</LineString>\n"
		<< "</Placemark>\n";

	combined = ss.str()+rr.str()+tt.str();
    return combined;
}

string Circle::createCircle() {
        ostringstream fulltext;
        string  omg;
        try {
                Geodesic geod(Constants::WGS84_a(), Constants::WGS84_f());
                {
                        double  points  = 100;
                        Circle  cir;

                        double  lat1    = coordinate.Latitude();
                        double  lon1    = coordinate.Longitude();
                        double  s12     = radius;
                        double  pi      = 360;
                        double  azi     = pi / points;
                        double  azi1    = 0;
                        double  lat2;
                        double  lon2;
                        int i;

                        for (i = 0; i <=points; ++i)
                        {
                                if (azi1 >= pi)
                                {
                                        azi1 = azi1 + azi - pi;
                                }
                                geod.Direct(lat1, lon1, azi1, s12, lat2, lon2);
                                azi1 = azi1 + azi;
                                fulltext << lon2 << "," << lat2 << ",0\n";
                        }
                }
        } catch (const exception& e) {
                cerr << "Caught exception: " << e.what() << "\n";
        }
        return fulltext.str();
}

void createZip(string filename, vector<Circle> circles)
{
    string data  = prepKml(circles);
    struct zip *zip = zip_open(filename.c_str(), ZIP_CREATE | ZIP_TRUNCATE, NULL);
    struct zip_source *compressed = zip_source_buffer(zip, data.c_str(), data.size(), 0);
    zip_file_add(zip, "Circlespots.kml", compressed, 0);
    zip_close(zip);
}

