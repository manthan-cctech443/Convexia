#pragma once
#include<vector>
using namespace std;

namespace Geometry {
	class GVector
	{
	private:
		double mX;
		double mY;
		double mZ;

	public:
		GVector(double x, double y, double z);
		~GVector();
		GVector operator-(GVector& other);
		static double magnitude(GVector& other);
		static double dotProduct(GVector vector1, GVector vector2);
		static GVector crossProduct(GVector vector1, GVector vector2);
	};
}