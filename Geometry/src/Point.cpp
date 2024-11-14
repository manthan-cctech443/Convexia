#include "Point.h"
#include <cmath>
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
	return mY; //(x2-x1)
}

int Point::Z()
{
	return mZ;
}

double Geometry::Point::pointDistance(vector<double> point1, vector<double> Point2)
{
	double dx = point1[0] - Point2[0];
	double dy = point1[1] - Point2[1];
	double dz = point1[2] - Point2[2];

	return sqrt(dx * dx + dy * dy + dz * dz);
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