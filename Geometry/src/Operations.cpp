#include "Operations.h"
#include "Dot.h"
using namespace Geometry;

double Geometry::pointDistance(Dot point1, Dot Point2)
{
	double dx = point1.X() - Point2.X();
	double dy = point1.Y() - Point2.Y();
	double dz = point1.Z() - Point2.Z();

	return sqrt(dx * dx + dy * dy + dz * dz);
}

double Geometry::distanceVectorToPoint(GVector vec, Dot pointP)
{
	GVector vecXpointP = Geometry::crossProduct(vec,pointP);
	double magnitudeVecXP = Geometry::magnitude(vecXpointP);

	double magnitudeVec = Geometry::magnitude(vec);

	double distanceLineToPoint = magnitudeVecXP / magnitudeVec;

	return distanceLineToPoint;
}

double Geometry::magnitude(GVector& other)
{
	return sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
}

double Geometry::dotProduct(GVector vec, GVector pointP)
{
	return vec.x * pointP.x + vec.y * pointP.y + vec.z * pointP.z;
}

Geometry:: GVector Geometry::crossProduct(GVector vec, Dot pointP)
{


	double X = vec.y * pointP.Z() - vec.z * pointP.Y();
	double Y = vec.z * pointP.X() - vec.x * pointP.Z();
	double Z = vec.x * pointP.Y() - vec.y * pointP.X();

	Dot res(X, Y, Z);

	return GVector(res);
}

GVector Geometry::crossProduct(GVector vec, GVector pointP)
{
	double X = vec.y * pointP.z - vec.z * pointP.y;
	double Y = vec.z * pointP.x - vec.x * pointP.z;
	double Z = vec.x * pointP.y - vec.y * pointP.x;

	Dot res(X, Y, Z);

	return GVector(res);
}

double Geometry::distanceToPlane(Face f, Dot pointP)
{
	GVector normal = getNormal(f.D1(), f.D2(), f.D3());
	GVector f1P(f.D1(), pointP);

	double normalDotf1P = dotProduct(normal, f1P);

	double distance = (normalDotf1P) / magnitude(normal);

	if(distance>0)	return (normalDotf1P) / magnitude(normal);
	return 0;			//visit again
}

Geometry:: GVector Geometry::getNormal(Dot A, Dot B, Dot C)
{
	GVector AB(A,B);
	GVector AC(A,C);
	GVector normal = crossProduct(AB, AC);
	return normal;
}
