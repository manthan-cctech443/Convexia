#include "Dot.h"

using namespace Geometry;

Geometry::Dot::Dot()
{
}

Dot::Dot(double x, double y, double z)
	: mX(x), mY(y), mZ(z)
{
}

Dot::~Dot()
{
}

double Dot::X()
{
	return mX;
}

double Dot::Y()
{
	return mY;
}

double Dot::Z()
{
	return mZ;
}

bool Dot::operator<(const Dot& other) const
{
	if (mX != other.mX) {
		return mX < other.mX;
	}
	if (mY != other.mY) {
		return mY < other.mY;
	}
	return mZ < other.mZ;
}