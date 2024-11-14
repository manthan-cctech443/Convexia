#include "Plane.h"

using namespace Geometry;
using namespace std;

Geometry::Plane::Plane(GVector A, GVector B, GVector C)
	:A(A),B(B),C(C)
{
}

Geometry::Plane::~Plane()
{
}
