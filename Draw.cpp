#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "GeographicLib/UTMUPS.hpp"			//Conversion of MGRS
#include "GeographicLib/MGRS.hpp"			//Conversion of MGRS
#include "GeographicLib/GeoCoords.hpp"      //GeoCoords class
#include "Circleplot.h"
#include "Exporter.h"
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Constants.hpp>

using namespace std;
using namespace GeographicLib;

// This has to be ran per instance of
void createCircle() {
	try {
		Geodesic geod(Constants::WGS84_a(), Constants::WGS84_f());
		{
			Circle 	cir;
			double	points	= 100;
			double 	lat1 	= cir.getLat();
			double	lon1 	= cir.getLon();
			double	s12 	= cir.getRealrad();
			double	azi 	= 360 / points;
			double	azi1	= 0;
			double 	lat2;
			double 	lon2;

			int i;
			for (i = 0; i <=points; ++i)
			{
				if (azi1 >= 360)
				{
					azi1 = azi1 + azi - 360;
				}
				azi1 = azi1 + azi;
				geod.Direct(lat1, lon1, azi1, s12, lat2, lon2);
				cout << "LAT: " << lat2 << " " << "LON: "<< lon2 << "\n";
			}
		}
	} catch (const exception& e) {
		cerr << "Caught exception: " << e.what() << "\n";
	}
}
