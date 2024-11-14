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

double Geometry::GVector::magnitude(GVector& other)
{
	return sqrt(other.mX * other.mX + other.mX * other.mY + other.mX * other.mZ);
}

double Geometry::GVector::dotProduct(GVector vector1, GVector vector2)
{
	return vector1.mX * vector2.mX + vector1.mY * vector2.mY + vector1.mZ * vector2.mZ;
}

GVector Geometry::GVector::crossProduct(GVector vector1, GVector vector2)
{

	double X = vector1.mY * vector2.mZ - vector1.mZ * vector2.mY;
	double Y = vector1.mZ * vector2.mX - vector1.mX * vector2.mZ;
	double Z = vector1.mX * vector2.mY - vector1.mY * vector2.mX;

	return { X,Y,Z };
}
