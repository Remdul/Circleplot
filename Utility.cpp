#include <iostream>
#include <string>
#include <sstream>
#include "Circleplot.h"
#include "Utility.h"

using namespace std;

string trim(std::string const& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last  = str.find_last_not_of(' ');
    return str.substr(first, last-first+1);
}

double stringToDouble(string convert)
{
    istringstream iss(convert);
    double converted = 0;
    iss >> converted;
    return converted;
}
