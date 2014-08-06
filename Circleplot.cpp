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

using namespace std;
using namespace GeographicLib;
std::ifstream file("data.txt");
std::string line;
typedef std::map<std::string, int, std::less<std::string> > map_type;

struct Circle {
public:
	string getSpot();
	double getRadius();
	string getMgrs();
	string getDesc();
	void setValues(string, string, string, string);
	void printValues();
private:
	string spot;
	string mgrs;
	string radius;
	string description;
};

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
	spot = sp;
	mgrs = mg;
	radius = ra;
	description = de;
}

void Circle::printValues() {
	cout << "Spot        : " << cutWhitespace(getSpot()) << endl;
	cout << "MGRS        : " << getMgrs() << endl;
	cout << "Radius      : " << getRadius() << " Meters" << endl;
	cout << "Description : " << cutQuotes(getDesc()) << endl;
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

string Circle::getMgrs() {
	string newmgrs = cutWhitespace(mgrs);
	int zone, prec;
	bool northp;
	double x, y;
	MGRS::Reverse(newmgrs, zone, northp, x, y, prec);
	double lat, lon;
	UTMUPS::Reverse(zone, northp, x, y, lat, lon);
	cout << "Lat/Lon     : " << prec << " Prec" << " " << lat << " Lat" << " " << lon << " Lon"<< "\n";
	return mgrs;
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
		cir.setValues(v[0], v[1], v[2], v[3]);
		cir.printValues();
	}
}
