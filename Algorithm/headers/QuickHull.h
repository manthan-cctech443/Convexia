#pragma once
#include <vector>
#include <tuple>
#include "Face.h"
#include "Dot.h"

using namespace std;
using namespace Geometry;

namespace Algorithm
{
	class QuickHull
	{

	public:
		QuickHull();
		~QuickHull();

		static vector<Face> quickHull(vector<Dot> points);

	private:

		static vector<Face> partOfHull;
		static vector<Face> convexHullFinal;
		static Dot centroid;

		static void generatenewFace(Face f, Dot pointP, vector<Dot>& points, vector<Face>& partOfHull, Dot& centroid);

		static tuple<int, Dot> farthestPointFromPlanePositive(Face f, vector<Dot> points);
		static tuple<int, Dot> farthestPointFromPlaneNegative(Face f, vector<Dot> points);

		static void quickHullRecursive(vector<Dot>& points, vector<Face>& partOfHull, Dot& centroid);

	};
}