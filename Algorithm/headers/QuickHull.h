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

		vector<Face> implementQuickHull(vector<Dot> points);

	private:

		void generatenewFace(Face face, Dot pointP, vector<Dot>& points, vector<Face>& partOfHull, Dot& centroid);

		tuple<int, Dot> farthestPointFromPlanePositive(Face face, vector<Dot>& points);
		tuple<int, Dot> farthestPointFromPlaneNegative(Face face, vector<Dot>& points);

		void quickHullRecursive(vector<Dot>& points, vector<Face>& partOfHull, vector<Face>& convexHullFinal, Dot& centroid);

	};
}