#include "QuickHull.h"
#include "Operations.h"
#include"Vector.h"

#include <algorithm>

using namespace Geometry;
using namespace Algorithm;

namespace Algorithm {
	vector<Face> partOfHull; 
	Dot centroid;
}
using namespace Algorithm;

vector<Face> Algorithm::quickHull(vector<Dot> points)
{
	vector<Face> partOfHull;
	vector<Dot> extreme;
	double minC = INT_MAX;
	double maxC = INT_MIN;
	for (int i = 0;i < points.size();i++) {
		Dot dmin,dmax;
		if (points[i].X() < minC)
		{
			minC = points[i].X();
			dmin = points[i];
		}
		if (points[i].X() > maxC) {
			maxC = points[i].X();
			dmax = points[i];
			
		}
		extreme.push_back(dmin);
		extreme.push_back(dmax);
	}

	minC = INT_MAX;
	maxC = INT_MIN;
	for (int i = 0;i < points.size();i++) {
		Dot dmin, dmax;
		if (points[i].Y() < minC)
		{
			minC = points[i].Y();
			dmin = points[i];
		}
		if (points[i].Y() > maxC) {
			maxC = points[i].Y();
			dmax = points[i];
		}
		extreme.push_back(dmin);
		extreme.push_back(dmax);
	}

	minC = INT_MAX;
	maxC = INT_MIN;
	for (int i = 0;i < points.size();i++) {
		Dot dmin, dmax;
		if (points[i].Z() < minC)
		{
			minC = points[i].Z();
			dmin = points[i];
		}
		if (points[i].Z() > maxC) {
			maxC = points[i].Z();
			dmax = points[i];
		}
		extreme.push_back(dmin);
		extreme.push_back(dmax);
	}

	set<Dot> uniqueExtremes(extreme.begin(),extreme.end());
	extreme.clear();
	extreme.insert(extreme.end(), uniqueExtremes.begin(), uniqueExtremes.end());

	double maxDistance = -1.0;
	Dot p1, p2;
	int j = 1;
	for (int i = 0;i < extreme.size();i++) {
		for(int j = 0;j< extreme.size();j++){
			if (i != j) {
				if (pointDistance(extreme[i], extreme[j]) > maxDistance) {
					maxDistance = pointDistance(extreme[i], extreme[j]);
					p1 = extreme[i];
					p2 = extreme[j];
				}
			}
		}
	}

	Dot p3;
	GVector p1p2 = GVector(p1,p2);
	double maxDistance1 = -1;
	for (int i = 0;i < extreme.size();i++) {
		if (distanceVectorToPoint(p1p2, extreme[i]) > maxDistance1) {
			maxDistance1 = distanceVectorToPoint(p1p2, extreme[i]);
			p3 = extreme[i];
		}
	}

	Face f1(p1, p2, p3);
	partOfHull.push_back(f1);
	Dot p4;
	double tempMaxDistance = -1;
	for (int i = 0;i < points.size();i++) {
		if (abs(distanceToPlane(f1, points[i])) > tempMaxDistance) {
			tempMaxDistance = distanceToPlane(f1, points[i]);
			p4 = points[i];
		}
	}

	Face f0(f1.D1(), f1.D2(), p4);
	Face f2(f1.D2(), f1.D3(), p4);
	Face f3(f1.D3(), f1.D1(), p4);

	partOfHull.push_back(f0);
	partOfHull.push_back(f2);
	partOfHull.push_back(f3);
	Dot centroid(((p1.X() + p2.X() + p3.X() + p4.X()) / 4.0), ((p1.Y() + p2.Y() + p3.Y() + p4.Y()) / 4.0), ((p1.Z() + p2.Z() + p3.Z() + p4.Z()) / 4.0));

	points.erase(remove(points.begin(), points.end(), p1), points.end());
	points.erase(remove(points.begin(), points.end(), p2), points.end());
	points.erase(remove(points.begin(), points.end(), p3), points.end());
	points.erase(remove(points.begin(), points.end(), p4), points.end());

	//quickHullRecursive(points,partOfHull);

	return partOfHull;
}

void Algorithm::generateFace(Face f, Dot pointP, vector<Dot> points)
{
	Face f1(f.D1(), f.D2(), pointP);
	Face f2(f.D2(), f.D3(), pointP);
	Face f3(f.D3(), f.D1(), pointP);

	partOfHull.push_back(f1);
	partOfHull.push_back(f2);
	partOfHull.push_back(f3);

	points.erase(remove(points.begin(), points.end(), pointP), points.end());
	partOfHull.erase(remove(partOfHull.begin(), partOfHull.end(), f), partOfHull.end());
}

Dot Algorithm::farthestPointFromPlanePositive(Face f, vector<Dot> points)
{
	Dot p;
	double maxDistance = -1;
	for (int i = 0;i < points.size();i++) {
		if (distanceToPlane(f, points[i]) > maxDistance) {
			maxDistance = distanceToPlane(f, points[i]);
			p = points[i];
		}
	}

	for (Dot i : points) {
		if (p == i)	return p;
	}
	//return p;
}

Dot Algorithm::farthestPointFromPlaneNegative(Face f, vector<Dot> points)
{
	Dot p;
	double maxDistance = 1;
	for (int i = 0;i < points.size();i++) {
		if (distanceToPlane(f, points[i]) < maxDistance) {
			maxDistance = distanceToPlane(f, points[i]);
			p = points[i];
		}
	}

	return p;
}

void Algorithm::quickHullRecursive(vector<Dot> points, vector<Face>& partOfHull)
{
	for (int i = 0;i<partOfHull.size();i++) {
		int c = 1;
		double d=distanceToPlane(partOfHull[i], centroid);
		if (d > 0) {
			Dot p=farthestPointFromPlaneNegative(partOfHull[i], points);
			generateFace(partOfHull[i], p, points);
			c = 1;
		}
		else {
			Dot p = farthestPointFromPlaneNegative(partOfHull[i], points);
			generateFace(partOfHull[i], p, points);
		}
	}
}
