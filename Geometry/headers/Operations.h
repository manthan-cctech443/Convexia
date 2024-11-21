#pragma once
#include "Dot.h"
#include"Face.h"
#include "GVector.h"
using namespace std;

namespace Geometry 
{
	class Operations 
	{
	public:

		Operations();
		~Operations();

		static double distancePointtoPoint(Dot point1,  Dot point2);
		static double distanceVectorToPoint(GVector vec,  Dot pointP);
		static double magnitude( GVector self);
		static double dotProduct(GVector vector1, GVector vector2);
		static GVector crossProduct(GVector vector1, GVector vector2);
		static GVector getNormal(Dot a,  Dot b,  Dot c);
		static double signeddistancePointToPlane(Face f,  Dot pointP);
	};
}