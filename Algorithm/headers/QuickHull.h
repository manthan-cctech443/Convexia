#pragma once
#include <set>
#include<vector>
#include "Face.h"
#include "Dot.h"
using namespace std;
using namespace Geometry;

namespace Algorithm
{
	vector<Face> quickHull(vector<Dot> points);

	void generateFace(Face f, Dot pointP, vector<Dot> points);

	Dot farthestPointFromPlane(Face f, vector<Dot> points);

	extern vector<Face> partOfHull;

	void quickHullRecursive(vector<Dot> points, vector<Face>& partOfHull);

	//set<vector<double>> outsideHull;
}