#include "Vector.h"
using namespace Geometry;

Geometry::GVector::GVector(Dot a, Dot b)
	:x(b.X() - a.X()),y(b.Y() - a.Y()),z(b.Z() - a.Z()), a(a), b(b)
{
}


Geometry::GVector::~GVector()
{
}