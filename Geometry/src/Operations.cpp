#include "Operations.h"
#include "Dot.h"
using namespace Geometry;

Operations::Operations()
{
}

Operations::~Operations()
{
}

double Operations::pointDistance(Dot point1, Dot point2)
{
	double dx = point1.X() - point2.X();
	double dy = point1.Y() - point2.Y();
	double dz = point1.Z() - point2.Z();

	return sqrt(dx * dx + dy * dy + dz * dz);
}

double Operations::distanceVectorToPoint(GVector vec, Dot pointP)
{
	Dot p1 = vec.a;
	GVector p1pointP(p1, pointP);
	GVector vecXpointP = Operations::crossProduct(p1pointP, vec);
	double magnitudeVecXP = Operations::magnitude(vecXpointP);

	double magnitudeVec = Operations::magnitude(vec);

	double distanceLineToPoint = magnitudeVecXP / magnitudeVec;

	return distanceLineToPoint;
}

double Operations::magnitude(GVector other)
{
	return sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
}

double Operations::dotProduct(GVector vector1, GVector vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

GVector Operations::crossProduct(GVector vec, Dot pointP)
{
	double resX = vec.y * pointP.Z() - vec.z * pointP.Y();
	double resY = vec.z * pointP.X() - vec.x * pointP.Z();
	double resZ = vec.x * pointP.Y() - vec.y * pointP.X();

	Dot res(resX, resY, resZ);
	Dot d(0.0, 0.0, 0.0);

	return GVector(d, res);
}

GVector Operations::crossProduct(GVector vector1, GVector vector2)
{
	double resX = vector1.y * vector2.z - vector1.z * vector2.y;
	double resY = vector1.z * vector2.x - vector1.x * vector2.z;
	double resZ = vector1.x * vector2.y - vector1.y * vector2.x;

	Dot res(resX, resY, resZ);
	Dot d(0.0, 0.0, 0.0);

	return GVector(d, res);
}

GVector Operations::getNormal(Dot a, Dot b, Dot c)
{
	GVector ab(a, b);
	GVector ac(a, c);
	GVector normal = crossProduct(ab, ac);
	return normal;
}

double Operations::distancePointToPlane(Face f, Dot pointP)
{
	GVector normal = getNormal(f.D1(), f.D2(), f.D3());
	GVector f1P(f.D1(), pointP);

	double normalDotf1P = dotProduct(normal, f1P);

	double distance = (normalDotf1P) / magnitude(normal);

	return distance;
}


