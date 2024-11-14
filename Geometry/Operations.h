#pragma once

#include"Plane.h"
#include "Vector.h"
#include<vector>
using namespace std;

namespace Geometry {
	double pointDistance(vector<double> point1, vector<double> Point2);
	double distanceVectorToPoint(GVector a, GVector b, GVector pointP);
	double magnitude(GVector& other);
	double dotProduct(GVector vector1, GVector vector2);
	GVector crossProduct(GVector vector1, GVector vector2);

	GVector getNormal(GVector A, GVector B, GVector C);
	double distanceToPlane(GVector A, GVector B, GVector C, GVector pointP);
}