#pragma once
#include<vector>
#include "Dot.h"
using namespace std;

namespace Geometry {
	class GVector
	{
	public:
		Dot a, b;
		double x, y, z;

		GVector(Dot a, Dot b);
		~GVector();
	};
}