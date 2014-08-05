#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
std::ifstream file("data.txt");
std::string line;

struct Circle
{
public:
	string 	getSpot();
	string 	getRadius();
	string 	getMgrs();
	string 	getDesc();
	void	setValues(string, string, string, string);
	void	printValues();
private:
	string	spot;
	string	radius;
	string	mgrs;
	string	description;
};

void Circle::setValues(string sp, string ra, string mg, string de)
{
	spot 		= sp;
	radius		= ra;
	mgrs		= mg;
	description = de;
}

void Circle::printValues()
{
	cout << "Spot        : " << spot << endl;
	cout << "Radius      : " << radius << endl;
	cout << "MGRS        : " << mgrs << endl;
	cout << "Description : " << description << endl;
	cout << endl;
}
string Circle::getSpot()
{
	return spot;

}

string Circle::getRadius()
{
	return radius;

}

string Circle::getMgrs()
{
	return mgrs;

}

string Circle::getDesc()
{
	return description;

}

void split (const string& s, char c, vector<string>& v)
{
	v.clear();
	string::size_type i = 0;
	string::size_type j = s.find(c);
	while (j != string::npos)
	{
		v.push_back(s.substr(i, j-i));
		i = ++j;
		j = s.find(c,j);
		if (j == string::npos)
		{
			v.push_back(s.substr(i, s.length()));
		}
	}
}

int main()
{
	Circle cir;
	vector<string> v;
	cir.setValues("woot1", "woot2", "woot3", "woot4");
	cir.printValues();

	while (std::getline(file, line))
    {
    	cout << line << endl;
    	split(line, ',', v);
    	cir.setValues(v[0],v[1],v[2],v[3]);
    	cir.printValues();
    }
}


