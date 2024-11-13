#include "Point.h"

using namespace Geometry;

Point::Point(int x, int y, int z)
	: mX(x), mY(y), mZ(z)
{
}

Point::~Point()
{
}

int Point::X()
{
	return mX;
}

int Point::Y()
{
	return mY;
}

int Point::Z()
{
	return mZ;
}

vector<double> Geometry::Point::getPoint(Triangulation& triangulation)
{
	Triangulation tri;
	point.push_back(triangulation.UniqueNumbers[p.X()]);
	point.push_back(triangulation.UniqueNumbers[p.Y()]);
	point.push_back(triangulation.UniqueNumbers[p.Z()]);
	return point;
}

void Geometry::Point::pointDistance(vector<double> point1, vector<double> Point2)
{
	return 
}

bool Point::operator<(const Point& other) const
{
	if (mX != other.mX) {
		return mX < other.mX;
	}
	if (mY != other.mY) {
		return mY < other.mY;
	}
	return mZ < other.mZ;
}