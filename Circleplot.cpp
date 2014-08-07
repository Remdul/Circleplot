/*
Compile using:
g++ -I/usr/local/include -I /usr/local/boost_1_55_0/ Circleplot.cpp -L /usr/local/boost_1_55_0/bin.v2/libs/regex/build/gcc-4.8.3/release/link-static/threading-multi/ -L /usr/local/lib -l boost_regex -l Geographic -std=c++11
*/

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
#include "boost/format.hpp"					// Purtifying Output


using namespace std;
using namespace GeographicLib;
using boost::format;
using boost::io::group;

std::ifstream file("data.txt");
std::string line;
typedef std::map<std::string, int, std::less<std::string> > map_type;

struct Circle {
public:
	string getSpot();
	double getRadius();
	GeoCoords getCoords();
	string getDesc();
	void setValues(string, string, string, string);
	void printValues();
private:
	string 		spot;
	GeoCoords 	coords;
	string 		radius;
	string 		description;
	double		lat;
	double		lon;
};
struct Point {
     Point( double X, double Y ): x(X), y(Y) {};
     double x;
     double y;
};//Simple Point structure

string cutWhitespace(string text) {
	boost::trim(text);
	boost::regex regexPattern { "[[:space:]]+", boost::regex_constants::egrep };
	string result = boost::regex_replace(text, regexPattern, "");
//	  cout << result << endl;
	return result;
}
string cutQuotes(string text) {
	boost::trim(text);
	boost::regex regexPattern { "(\\s)*(\")", boost::regex_constants::egrep };
	string result = boost::regex_replace(text, regexPattern, "");
//	  cout << result << endl;
	return result;
}

void Circle::setValues(string sp, string mg, string ra, string de) {
	GeoCoords c(mg);
	spot 		= sp;
	coords 		= c;
	radius 		= ra;
	description = de;
	lat 		= c.Latitude();
	lon			= c.Longitude();
}

void Circle::printValues() {
	cout << format("+--------------------------------------------------------+\n");
	cout << format("| %+11s : %-40s |") % "Spot" 		% cutWhitespace(getSpot()) << endl;
    cout << format("| %+11s : %-40s |") % "MGRS" 		% getCoords().MGRSRepresentation() << endl;
    cout << format("| %+11s : %-40s |") % "Latitude" 	% getCoords().Latitude() << endl;
    cout << format("| %+11s : %-40s |") % "Longitude" 	% getCoords().Longitude() << endl;
    cout << format("| %+11s : %-5s %-34s |") % "Radius" 		% getRadius() % "Meters" << endl;
    cout << format("| %+11s : %-40s |") % "Description" 	% cutQuotes(getDesc()) << endl;
	cout << format("+--------------------------------------------------------+\n");

	cout << endl;
}
string Circle::getSpot() {
	return spot;
}

double Circle::getRadius() {
	const string pattern = "([0-9.\\s]*)([a-zA-Z]*)";
	const string target = cutWhitespace(radius);
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

GeoCoords Circle::getCoords() {
	return coords;
}

string Circle::getDesc() {
	return description;
}

void split(const string& s, char c, vector<string>& v) {
	v.clear();
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
}

int main() {
	Circle cir;
	vector<string> v;
	while (std::getline(file, line)) {
		cout << line << endl;
		split(line, ',', v);

		cir.setValues(v[0], cutWhitespace(v[1]), v[2], v[3]);
		cir.printValues();
	}
}
