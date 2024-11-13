#pragma once
#include "Reader.h"
using namespace std;

class OBJReader : public Reader
{
	vector<Point> vertices;
public:
	OBJReader();
	~OBJReader();

	void read(const std::string& fileName, Triangulation& tri);
	bool operator()(double a, double b) const;

	vector<Point> getPoints();
};