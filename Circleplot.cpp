#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include "libzip/lib/zip.h"
#include <boost/regex.hpp>					//Boost REGEX
#include <boost/algorithm/string/trim.hpp> 	//Boost Trim
#include <boost/lexical_cast.hpp>			//Converts strings to numbers
#include <stdlib.h>							//For double conversion from string
#include "GeographicLib/UTMUPS.hpp"			//Conversion of MGRS
#include "GeographicLib/MGRS.hpp"			//Conversion of MGRS
#include "GeographicLib/GeoCoords.hpp"      //GeoCoords class
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Constants.hpp>
#include "boost/format.hpp"					// Purtifying Output
#include "Circleplot.h"
#include "Exporter.h"

using namespace std;
using namespace GeographicLib;
using boost::format;
using boost::io::group;

int answer;
ifstream file("data.txt");
string line;

string cutWhitespace(string text) {
	boost::trim(text);
	boost::regex regexPattern { "[[:space:]]+", boost::regex_constants::egrep };
	string result = boost::regex_replace(text, regexPattern, "");
	return result;
}
string cutQuotes(string text) {
	boost::trim(text);
	boost::regex regexPattern { "(\\s)*(\")", boost::regex_constants::egrep };
	string result = boost::regex_replace(text, regexPattern, "");
	return result;
}

void Circle::setValues(string sp, string mg, string ra, string de) {
	GeoCoords c(mg);
	spot 		= sp;
	coords 		= c;
	radius 		= getRadius(ra);
	description = de;
	lat 		= c.Latitude();
	lon			= c.Longitude();
}

void Circle::printValues() {
	cout << format("+--------------------------------------------------------+\n");
	cout << format("| %+11s : %-40s |") % "Spot" 		% cutWhitespace(getSpot()) 			<< endl;
    cout << format("| %+11s : %-40s |") % "MGRS" 		% getCoords().MGRSRepresentation() 	<< endl;
    cout << format("| %+11s : %-40s |") % "Latitude" 	% getLat() 							<< endl;
    cout << format("| %+11s : %-40s |") % "Longitude" 	% getLon() 							<< endl;
    cout << format("| %+11s : %-5s %-34s |") % "Radius" % getRealrad() % "Meters" 			<< endl;
    cout << format("| %+11s : %-40s |") % "Description" % cutQuotes(getDesc()) 				<< endl;
	cout << format("+--------------------------------------------------------+\n");

	cout << endl;
}
string Circle::getSpot() {
	return spot;
}

double Circle::getRadius(string inRad) {
	const string pattern = "([0-9.\\s]*)([a-zA-Z]*)";
	const string target = cutWhitespace(inRad);
	int measurement;
	double convRad;
	double unconvRad;
	boost::regex regexPattern(pattern, boost::regex::extended);
	boost::smatch what;

	bool isMatchFound = boost::regex_match(target, what, regexPattern);
	if (isMatchFound) {
		if (what[2] == "M") {
			measurement = 1;
		} else if (what[2] == "KM") {
			measurement = 1000;
		}
		unconvRad = boost::lexical_cast<double>(what[1]);
		convRad = unconvRad * measurement;
	} else {
		cout << "Gah. No match found for: " << radius << endl;
	}
	return convRad;
}

double Circle::getRealrad ()
{
	return radius;
}

GeoCoords Circle::getCoords() {
	return coords;
}

string Circle::getDesc() {
	return description;
}

double Circle::getLat() {
	return lat;
}
double Circle::getLon() {
	return lon;
}

vector<string> split(const string& s, char c) {
    vector<string> v;
	string::size_type i = 0;
	string::size_type j = s.find(c);
	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);
		if (j == string::npos) {
			v.push_back(s.substr(i, s.length()));
		}
	}
	return v;
}

void processFile()
{
	Circle cir;
	vector<string> v;
	while (std::getline(file, line)) {
		cout << line << endl;
		v = split(line, ',');

		cir.setValues(v[0], cutWhitespace(v[1]), v[2], v[3]);
		cir.printValues();
	}
}

void printKml() {
	ofstream handle;
	Circle cir;
	string cutSpot;
	string filePre = "CircleSpots.kml";
	vector<Circle> buildKML;
	vector<string> v;

	/* Load the File */

	handle.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	const char * filename = filePre.c_str();
	handle.open(filename);
	handle << prepKml();
	handle.close();
}

string prepKml()
{
    ostringstream stream;
    Circle cir;
    vector<string> v;

    stream << "<?xml version='1.0' encoding='utf-8'?>\n";
    stream << "<kml xmlns='http://www.opengis.net/kml/2.2'>\n";
    stream << "<Document>\n";
    while (std::getline(file, line)) {
        cout << line << endl;
        v = split(line, ',');
        cir.setValues(v[0], cutWhitespace(v[1]), v[2], cutQuotes(v[3]));
        stream << cir.FormatPlacemark();
    }
    stream << "</Document>\n";
    stream << "</kml>\n";
    return stream.str();
}

void createZip()
{
    string file = "Circlespots.kml";
    char *data  = prepKml().c_str();

    int error = 0;
    zip *archive = zip_open("Circleplot.zip", 0, &error);
    zip_source *source = zip_source_buffer(archive, data, sizeof(data), 0);
    int index = (int)zip_file_add(archive, file.c_str(), source, ZIP_FL_OVERWRITE);
}

string Circle::createCircle() {
	ostringstream fulltext;
	string 	omg;
	try {
		Geodesic geod(Constants::WGS84_a(), Constants::WGS84_f());
		{
			double	points	= 100;
			Circle 	cir;

			double 	lat1 	= getLat();
			double	lon1 	= getLon();
			double	s12 	= getRealrad();
			double	pi		= 360;
			double	azi 	= pi / points;
			double	azi1	= 0;
			double 	lat2;
			double 	lon2;
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


int mainLoop()
{
	vector<string> v;
	Circle cir;

	cout << "Welcome to Bryan Elliott's Map Circle Maker!" 				<< endl;
	cout << "+------------------------------------------+" 				<< endl;
	cout << format("|%-42s|") % "What would you like to do?" 			<< endl;
	cout << format("|%-42s|") % "0) Quit. I didn't want to be here." 	<< endl;
	cout << format("|%-42s|") % "1) Process File and Display Details"	<< endl;
	cout << format("|%-42s|") % "2) Export KML File"					<< endl;
	cout << format("|%-42s|") % "3) Create Circle. Temp" 				<< endl;
	cout << "+------------------------------------------+" 				<< endl;
	cout << ">> ";
	cin >> answer;
	if (answer == 0) {
		cout << "Fine. Quitting..." << endl;
		return 0;
	} else if (answer == 1) {
		cout << "Processing File..." << endl;
		processFile();
		return 0;
	}

	else if (answer == 2) {
	    cout << "Export File To:" << endl;
	    cout << "1) Zip File" << endl;
	    cout << "2) KML File Only" << endl;
	    int subanswer = cin;
	    if (cin == 1)
	    {
            cout << "Exporting ZIP File..." << endl;
	        createZip();
	    }
	    else if (cin == 2)
	    {
	        cout << "Exporting KML File..." << endl;
	        printKml();
	    }
	    else
	    {
	        cout << "Uhm... invalid answer..." << endl;
	        break;
	    }
	    cout << "Completed." << endl;
		return 0;
	} else if (answer == 3) {
		cout << "Creating Circle..." << endl;
		while (std::getline(file, line)) {
			cout << line << endl;
			v = split(line, ',');
			cir.setValues(v[0], cutWhitespace(v[1]), v[2], cutQuotes(v[3]));
			cout << cir.createCircle();
			cout << "------------------------------" << endl << endl << endl;
		}
		return 0;
	} else {
		cout << "Invalid choice." << endl;
		return 0;
	}
	return answer;
}
int main() {

	mainLoop();
	return 0;
}
