#pragma once
#include<vector>
using namespace std;

namespace Geometry {
	class GVector
	{
	public:
		double mX;
		double mY;
		double mZ;

		GVector(double x, double y, double z);
		~GVector();
		GVector operator-(GVector& other);
	};
}