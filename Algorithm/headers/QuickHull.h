#pragma once
#include <set>
#include<vector>
#include "Face.h"
#include "Dot.h"
using namespace std;
using namespace Geometry;

namespace Algorithm
{
	void quickHull(vector<Dot> points);

	void generateFace(Face f, Dot pointP);

	Dot farthestPointFromPlane(Face f, vector<Dot> points);

	vector<Face> partOfHull;

	//set<vector<double>> outsideHull;
}