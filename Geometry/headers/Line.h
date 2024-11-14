#pragma once
#include "Vector.h"

#include <vector>
using namespace std;

namespace Geometry {
	class Line
	{
		GVector mLine;
	public:
		Line(GVector a, GVector b);
		~Line();
		double distanceToPoint(GVector a, GVector b, GVector pointP);
	};
}

