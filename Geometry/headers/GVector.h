#pragma once
#include "Dot.h"

using namespace std;

namespace Geometry {
	class GVector
	{

	public:

		GVector();
		GVector(Dot a, Dot b);
		~GVector();

		double X();
		double Y();
		double Z();

		Dot A;
		Dot B;

	private:

		double mX;
		double mY;
		double mZ;

	};
}