#pragma once
#include <set>
#include<vector>
#include <tuple>
#include "Face.h"
#include "Dot.h"
using namespace std;
using namespace Geometry;

namespace Algorithm
{
	vector<Face> quickHull(vector<Dot> points);

	void generateFace(Face f, Dot pointP, vector<Dot>& points, vector<Face>& partOfHull);

	tuple<int, Dot> farthestPointFromPlanePositive(Face f, vector<Dot> points);
	tuple<int, Dot> farthestPointFromPlaneNegative(Face f, vector<Dot> points);

	extern vector<Face> partOfHull;
	extern vector<Face> ConvexHullFinal;
	extern Dot centroid;

	void quickHullRecursive(vector<Dot>& points, vector<Face>& partOfHull, Dot& centroid);
}