#pragma once
#include "Dot.h"
#include"Face.h"
#include "Vector.h"
#include<vector>
using namespace std;

namespace Geometry {
	double pointDistance(Dot point1, Dot Point2);
	double distanceVectorToPoint(GVector vec, Dot pointP);
	double magnitude(GVector& other);
	double dotProduct(GVector vector1, GVector vector2);
	GVector crossProduct(GVector vec, Dot pointP);
	GVector crossProduct(GVector vector1, GVector vector2);
	GVector getNormal(Dot A, Dot B, Dot C);
	double distanceToPlane(Face f,Dot pointP);
}