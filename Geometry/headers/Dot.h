#pragma once

namespace Geometry
{

	class Dot
	{
		double mX;
		double mY;
		double mZ;

		bool operator<(const Dot& other) const;

	public:
		Dot();
		Dot(double x, double y, double z);
		~Dot();

		double X();
		double Y();
		double Z();

		bool operator==(const Dot& other)const;
	};
}