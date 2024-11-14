#include "Operations.h"

using namespace Geometry;

double Geometry::pointDistance(vector<double> point1, vector<double> Point2)
{
	double dx = point1[0] - Point2[0];
	double dy = point1[1] - Point2[1];
	double dz = point1[2] - Point2[2];

	return sqrt(dx * dx + dy * dy + dz * dz);
}

double Geometry::distanceVectorToPoint(GVector a, GVector b, GVector pointP)
{
	GVector distanceAP = GVector(pointP - a);
	GVector distanceAB = GVector(b - a);


	GVector apXab = Geometry::crossProduct(distanceAP, distanceAB);
	double magnitudeAB = Geometry::magnitude(distanceAB);

	double magnitudeAPxAB = Geometry::magnitude(apXab);

	double distanceLineToPoint = magnitudeAPxAB / magnitudeAB;

	return distanceLineToPoint;
}

double Geometry::magnitude(GVector& other)
{
	return sqrt(other.mX * other.mX + other.mX * other.mY + other.mX * other.mZ);
}

double Geometry::dotProduct(GVector vector1, GVector vector2)
{
	return vector1.mX * vector2.mX + vector1.mY * vector2.mY + vector1.mZ * vector2.mZ;
}

Geometry:: GVector Geometry::crossProduct(GVector vector1, GVector vector2)
{
	double X = vector1.mY * vector2.mZ - vector1.mZ * vector2.mY;
	double Y = vector1.mZ * vector2.mX - vector1.mX * vector2.mZ;
	double Z = vector1.mX * vector2.mY - vector1.mY * vector2.mX;

	return { X,Y,Z };
}

Geometry:: GVector Geometry::getNormal(GVector A, GVector B, GVector C)
{
	GVector AB = B - A;
	GVector AC = C - A;
	GVector normal = crossProduct(AB, AC);
	return normal;
}

double Geometry::distanceToPlane(GVector A, GVector B, GVector C, GVector pointP)
{
	GVector normal = getNormal(A, B, C);
	double dist = dotProduct(normal, A);

	return abs(dotProduct(normal, pointP) - dist) / magnitude(normal);
}
