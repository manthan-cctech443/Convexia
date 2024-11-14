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

GVector Geometry::Plane::getNormal()
{
	GVector AB = B - A;
	GVector AC = C - A;
	GVector normal = GVector::crossProduct(AB, AC);
	return normal;
}

double Geometry::Plane::distanceToPlane(GVector pointP)
{
	GVector normal = getNormal();
	double dist = GVector::dotProduct(normal, A);

	return abs(GVector::dotProduct(normal, pointP) - dist) / GVector::magnitude(normal);
}
