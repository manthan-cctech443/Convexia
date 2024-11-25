#pragma once
#include<vector>
#include "Dot.h"
using namespace std;

namespace Geometry {
	class GVector
	{
		Dot a;
		Dot b;
		double mX;
		double mY;
		double mZ;
	public:
		GVector();
		GVector(Dot a, Dot b);
		~GVector();

		double X();
		double Y();
		double Z();

		Dot A;
		Dot B;
	};
}