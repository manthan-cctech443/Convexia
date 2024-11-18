#include "Vector.h"
using namespace Geometry;

Geometry::GVector::GVector()
{
}

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
