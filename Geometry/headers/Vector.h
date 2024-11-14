#pragma once
#include<vector>
#include "Dot.h"
using namespace std;

namespace Geometry {
	class GVector
	{
	public:
		double x, y, z;

		GVector(Dot a);
		GVector(Dot a, Dot b);
		~GVector();
	};
}