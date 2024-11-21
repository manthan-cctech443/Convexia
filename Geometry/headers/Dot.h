#pragma once

namespace Geometry
{

	class Dot
	{

	public:

		Dot();
		Dot(double x, double y, double z);
		~Dot();

		double X();
		double Y();
		double Z();

		bool operator<(const Dot& other) const;
		bool operator==(const Dot& other)const;

	private :

		double mX;
		double mY;
		double mZ;

	};
}