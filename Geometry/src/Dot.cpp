#include "Dot.h"

using namespace Geometry;

Geometry::Dot::Dot()
	:mX(0), mY(0), mZ(0)
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

bool Geometry::Dot::operator==(const Dot& other) const
{
	return mX == other.mX &&
		mY == other.mY &&
		mZ == other.mZ;
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