#include "Vector.h"
using namespace Geometry;

Geometry::GVector::GVector(double x, double y, double z)
	:mX(x),mY(y),mZ(z)
{
}

Geometry::GVector::~GVector()
{
}

GVector Geometry::GVector::operator-(GVector& other)
{
	return GVector(mX-other.mX,mY-other.mY,mZ-other.mZ);
}
