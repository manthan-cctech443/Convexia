#include "Operations.h"
#include <cmath>

using namespace Geometry;

Operations::Operations()
{
}

Operations::~Operations()
{
}

double Operations::distancePointToPoint(Dot point1, Dot point2)
{
	double dx = point1.X() - point2.X();
	double dy = point1.Y() - point2.Y();
	double dz = point1.Z() - point2.Z();

	return sqrt(dx * dx + dy * dy + dz * dz);
}

double Operations::distanceVectorToPoint(GVector vec, Dot pointP)
{
	Dot p1 = vec.A;
	GVector p1pointP(p1, pointP);
	GVector vecXpointP = Operations::crossProduct(p1pointP, vec);
	double magnitudeVecXP = Operations::magnitude(vecXpointP);

	double magnitudeVec = Operations::magnitude(vec);

	double distanceLineToPoint = magnitudeVecXP / magnitudeVec;

	return distanceLineToPoint;
}

double Operations::magnitude(GVector self)
{
	return sqrt(self.X() * self.X() + self.Y() * self.Y() + self.Z() * self.Z());
}

double Operations::dotProduct(GVector vector1, GVector vector2)
{
	return vector1.X() * vector2.X() + vector1.Y() * vector2.Y() + vector1.Z() * vector2.Z();
}

GVector Operations::crossProduct(GVector vector1, GVector vector2)
{
	double resX = vector1.Y() * vector2.Z() - vector1.Z() * vector2.Y();
	double resY = vector1.Z() * vector2.X() - vector1.X() * vector2.Z();
	double resZ = vector1.X() * vector2.Y() - vector1.Y() * vector2.X();

	Dot res(resX, resY, resZ);
	Dot d(0.0, 0.0, 0.0);

	return GVector(d, res);
}

GVector Operations::getNormal(Dot a, Dot b, Dot c)
{
	GVector ab(a, b);
	GVector ac(a, c);

	return crossProduct(ab, ac);
}

//sign indicates whether the point is in front of or behind the plane.
double Operations::signedDistancePointToPlane(Face f, Dot pointP)
{
	GVector normal = getNormal(f.D1(), f.D2(), f.D3());
	GVector f1P(f.D1(), pointP);

	double normalDotf1P = dotProduct(normal, f1P);

	double signedDistance = (normalDotf1P) / magnitude(normal);

	return signedDistance;
}
