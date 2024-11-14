#include "Line.h"
using namespace Geometry;

Line::Line(GVector a, GVector b)
	: mLine(b-a)
{
}

Line::~Line()
{
}

double Line::distanceToPoint(GVector a, GVector b, GVector pointP)
{
	GVector distanceAP = GVector(pointP - a);
	GVector distanceAB = GVector(b - a);
	

	GVector apXab = GVector::crossProduct(distanceAP, distanceAB);
	double magnitudeAB = GVector::magnitude(distanceAB);

	double magnitudeAPxAB = GVector::magnitude(apXab);

	double distanceLineToPoint = magnitudeAPxAB / magnitudeAB;

	return distanceLineToPoint;
}
