#include "GVector.h"

using namespace Geometry;

Geometry::GVector::GVector()
	:mX(0), mY(0), mZ(0), A(), B()
	{
	}

// Constructor that creates a vector from two points (a and b), where the vector is b - a.
Geometry::GVector::GVector(Dot a, Dot b)
	:mX(b.X() - a.X()), mY(b.Y() - a.Y()), mZ(b.Z() - a.Z()), A(a), B(b)
{
}


Geometry::GVector::~GVector()
{
}

double Geometry::GVector::X()
{
	return mX;
}

double Geometry::GVector::Y()
{
	return mY;
}

double Geometry::GVector::Z()
{
	return mZ;
}
