#pragma once
#include "Triangulation.h"
#include<vector>

using namespace std;

namespace Geometry
{
	class Point
	{
		int mX;
		int mY;
		int mZ;
		vector<double>point;

	public:
		Point(int x, int y, int z);
		~Point();

		int X();
		int Y();
		int Z();

		vector<double> getPoint(Triangulation& triangulation);
		void pointDistance(vector<double> point1, vector<double> Point2);

		bool operator<(const Point& other) const;
	};
}