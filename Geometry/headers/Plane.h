#pragma once
#include "Vector.h"

namespace Geometry {
	class Plane
	{
		GVector A;
		GVector B;
		GVector C;
	public:
		Plane(GVector A, GVector B, GVector C);
		~Plane();

		GVector getNormal();
		double distanceToPlane(GVector pointP);
	};
}
