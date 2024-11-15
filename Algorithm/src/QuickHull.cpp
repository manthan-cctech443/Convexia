#include "QuickHull.h"
#include "Operations.h"
#include"Vector.h"
using namespace Geometry;

void Algorithm::quickHull(vector<Dot> points)
{
	/*vector<Face> partOfHul;*/
	vector<Dot> extreme;
	double minC = INT_MAX;
	double maxC = INT_MIN;
	for (int i = 0;i < points.size();i++) {
		if (points[i].X() < minC)
		{
			minC = points[i].X();
			extreme.push_back(points[i]);
		}
		if (points[i].X() > maxC) {
			maxC = points[i].X();
			extreme.push_back(points[i]);
		}
	}

	minC = INT_MAX;
	maxC = INT_MIN;
	for (int i = 0;i < points.size();i++) {
		if (points[i].Y() < minC)
		{
			minC = points[i].Y();
			extreme.push_back(points[i]);
		}
		if (points[i].Y() > maxC) {
			maxC = points[i].Y();
			extreme.push_back(points[i]);
		}
	}

	minC = INT_MAX;
	maxC = INT_MIN;
	for (int i = 0;i < points.size();i++) {
		if (points[i].Z() < minC)
		{
			minC = points[i].Z();
			extreme.push_back(points[i]);
		}
		if (points[i].Z() > maxC) {
			maxC = points[i].Z();
			extreme.push_back(points[2]);
		}
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
	maxDistance = -1;
	for (int i = 0;i < extreme.size();i++) {
		if (distanceVectorToPoint(p1p2, extreme[i]) > maxDistance) {
			maxDistance = distanceVectorToPoint(p1p2, extreme[i]);
			p3 = extreme[i];
		}
	}

	Face f1(p1, p2, p3);
	partOfHull.push_back(f1);
	Dot p4 = farthestPointFromPlane(f1,points);

}

void Algorithm::generateFace(Face f, Dot pointP)
{
	Face f1(f.D1(), f.D2(), pointP);
	Face f2(f.D2(), f.D3(), pointP);
	Face f3(f.D3(), f.D1(), pointP);

	partOfHull.push_back(f1);
	partOfHull.push_back(f2);
	partOfHull.push_back(f3);
}

Dot Algorithm::farthestPointFromPlane(Face f, vector<Dot> points)
{
	Dot p;
	double maxDistance = -1;
	for (int i = 0;i < points.size();i++) {
		if (distanceToPlane(f, points[i]) > maxDistance) {
			maxDistance = distanceToPlane(f, points[i]);
			p = points[i];
		}
	}

	return p;
}
