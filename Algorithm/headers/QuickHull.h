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

		vector<Face> quickHull(vector<Dot> points);

	private:

		vector<Face> partOfHull;
		vector<Face> convexHullFinal;
		Dot centroid;

		void generatenewFace(Face f, Dot pointP, vector<Dot>& points, vector<Face>& partOfHull, Dot& centroid);

		tuple<int, Dot> farthestPointFromPlanePositive(Face f, vector<Dot> points);
		tuple<int, Dot> farthestPointFromPlaneNegative(Face f, vector<Dot> points);

		void quickHullRecursive(vector<Dot>& points, vector<Face>& partOfHull, Dot& centroid);

	};
}