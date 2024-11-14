#pragma once
#include "Triangulation.h"
#include<vector>
#include<iostream>

using namespace std;

namespace Geometry
{
	class Point
	{
		int mX;
		int mY;
		int mZ;

	public:
		Point(int x, int y, int z);
		~Point();

		int X();
		int Y();
		int Z();

		double pointDistance(vector<double> point1, vector<double> Point2);

		bool operator<(const Point& other) const;
	};
}