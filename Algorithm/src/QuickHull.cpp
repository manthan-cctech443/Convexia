#include "QuickHull.h"
#include "Operations.h"
#include "Vector.h"
#include "Face.h"
#include <set>

using namespace Algorithm;

Algorithm::QuickHull::QuickHull()
{
}

Algorithm::QuickHull::~QuickHull()
{
}

std::vector<Face> Algorithm::QuickHull::partOfHull;
std::vector<Face> Algorithm::QuickHull::convexHullFinal;

vector<Face> Algorithm::QuickHull::quickHull(vector<Dot> points)
{
	set<Dot> extremePointset; // To store extreme points along all 3 axes.

	//Find extreme points X-axis.

	double minC = INT_MAX;
	double maxC = INT_MIN;
	for (int i = 0; i < points.size(); i++)
	{
		Dot dmin, dmax;
		if (points[i].X() < minC)
		{
			minC = points[i].X();
			dmin = points[i];
		}
		if (points[i].X() > maxC)
		{
			maxC = points[i].X();
			dmax = points[i];

		}
		extremePointset.insert(dmin);
		extremePointset.insert(dmax);
	}

	//Find extreme points Y-axis.

	minC = INT_MAX;
	maxC = INT_MIN;
	for (int i = 0; i < points.size(); i++)
	{
		Dot dmin, dmax;
		if (points[i].Y() < minC)
		{
			minC = points[i].Y();
			dmin = points[i];
		}
		if (points[i].Y() > maxC)
		{
			maxC = points[i].Y();
			dmax = points[i];
		}
		extremePointset.insert(dmin);
		extremePointset.insert(dmax);
	}

	//Find extreme points Z-axis.

	minC = INT_MAX;
	maxC = INT_MIN;
	for (int i = 0; i < points.size(); i++)
	{
		Dot dmin, dmax;
		if (points[i].Z() < minC)
		{
			minC = points[i].Z();
			dmin = points[i];
		}
		if (points[i].Z() > maxC)
		{
			maxC = points[i].Z();
			dmax = points[i];
		}
		extremePointset.insert(dmin);
		extremePointset.insert(dmax);
	}


	vector<Dot> extreme;
	extreme.insert(extreme.end(), extremePointset.begin(), extremePointset.end());

	//Find 2 farthest points among the extreme points.

	double maxDistance = -1.0;
	Dot p1, p2;
	for (int i = 0; i < extreme.size(); i++)
	{
		for (int j = 0; j < extreme.size(); j++)
		{
			if (i != j)
			{
				if (Operations::pointDistance(extreme[i], extreme[j]) > maxDistance)
				{
					maxDistance = Operations::pointDistance(extreme[i], extreme[j]);
					p1 = extreme[i];
					p2 = extreme[j];
				}
			}
		}
	}

	Dot p3;
	GVector p1p2 = GVector(p1, p2);

	//Find the farthest point from the line.

	maxDistance = -1;
	for (int i = 0; i < extreme.size(); i++)
	{
		if (Operations::distanceVectorToPoint(p1p2, extreme[i]) > maxDistance)
		{
			maxDistance = Operations::distanceVectorToPoint(p1p2, extreme[i]);
			p3 = extreme[i];
		}
	}

	Face f1(p1, p2, p3);
	partOfHull.push_back(f1);

	//Find the farthest point from the face.

	Dot p4;
	maxDistance = -1;
	for (int i = 0; i < points.size(); i++)
	{
		if (abs(Operations::distancePointToPlane(f1, points[i])) > maxDistance)
		{
			maxDistance = abs(Operations::distancePointToPlane(f1, points[i]));
			p4 = points[i];
		}
	}

	//generate faces for the initial hull.

	Face f0(f1.D1(), f1.D2(), p4);
	Face f2(f1.D2(), f1.D3(), p4);
	Face f3(f1.D3(), f1.D1(), p4);

	partOfHull.push_back(f0);
	partOfHull.push_back(f2);
	partOfHull.push_back(f3);

	Dot centroid(((p1.X() + p2.X() + p3.X() + p4.X()) / 4.0), ((p1.Y() + p2.Y() + p3.Y() + p4.Y()) / 4.0), ((p1.Z() + p2.Z() + p3.Z() + p4.Z()) / 4.0));

	//Remove points that are partofHull.

	points.erase(remove(points.begin(), points.end(), p1), points.end());
	points.erase(remove(points.begin(), points.end(), p2), points.end());
	points.erase(remove(points.begin(), points.end(), p3), points.end());
	points.erase(remove(points.begin(), points.end(), p4), points.end());

	quickHullRecursive(points, partOfHull, centroid);

	return convexHullFinal;
}




tuple<int, Dot> Algorithm::QuickHull::farthestPointFromPlanePositive(Face f, vector<Dot> points)
{
	Dot p;
	double maxDistance = -1;
	for (int i = 0; i < points.size(); i++)
	{
		if (Operations::distancePointToPlane(f, points[i]) > maxDistance)
		{
			maxDistance = Operations::distancePointToPlane(f, points[i]);
			p = points[i];
		}
	}
	if (maxDistance > 0)
	{
		return { 1, p };
	}
	else
	{
		return { 0, p };
	}
}

tuple<int, Dot> Algorithm::QuickHull::farthestPointFromPlaneNegative(Face f, vector<Dot> points)
{
	Dot p;
	double maxDistance = 1;
	for (int i = 0; i < points.size(); i++)
	{
		if (Operations::distancePointToPlane(f, points[i]) < maxDistance)
		{
			maxDistance = Operations::distancePointToPlane(f, points[i]);
			p = points[i];
		}
	}

	if (maxDistance < 0)
	{
		return { 1, p };
	}
	else
	{
		return { 0, p };
	}
}

void Algorithm::QuickHull::generatenewFace(Face f, Dot pointP, vector<Dot>& points, vector<Face>& partOfHull, Dot& centroid)
{
	vector<Face> visibleFaces;
	for (Face f : partOfHull)
	{
		double dis = Operations::distancePointToPlane(f, centroid);
		double d = Operations::distancePointToPlane(f, pointP);
		if (d * dis < 0)
		{
			visibleFaces.push_back(f);
		}
	}
	for (Face f : visibleFaces)
	{
		Face f1(f.D1(), f.D2(), pointP);
		Face f2(f.D2(), f.D3(), pointP);
		Face f3(f.D3(), f.D1(), pointP);

		partOfHull.push_back(f1);
		partOfHull.push_back(f2);
		partOfHull.push_back(f3);

		partOfHull.erase(remove(partOfHull.begin(), partOfHull.end(), f), partOfHull.end());
	}
	if (visibleFaces.size() > 1)
	{
		for (int i = 0; i < partOfHull.size() - 1; i++)
		{
			for (int j = i + 1; j < partOfHull.size(); j++)
			{
				if (partOfHull[i] == partOfHull[j] )
				{
					Face fw = partOfHull[i]; 
					size_t len = partOfHull.size();
					partOfHull.erase(remove(partOfHull.begin(), partOfHull.end(), fw), partOfHull.end());
					break;
				}
			}
		}
	}
	points.erase(remove(points.begin(), points.end(), pointP), points.end());
}

void Algorithm::QuickHull::quickHullRecursive(vector<Dot>& points, vector<Face>& partOfHull, Dot& centroid)
{
	while (partOfHull.size() != 0)
	{
		double dis = Operations::distancePointToPlane(partOfHull[0], centroid);
		tuple<int, Dot> t;
		if (dis > 0)
		{
			t = farthestPointFromPlaneNegative(partOfHull[0], points);
		}
		else if (dis < 0)
		{
			t = farthestPointFromPlanePositive(partOfHull[0], points);
		}
		if (get<0>(t) == 1)
		{
			generatenewFace(partOfHull[0], get<1>(t), points, partOfHull, centroid);
		}
		else
		{
			convexHullFinal.push_back(partOfHull[0]);
			partOfHull.erase(remove(partOfHull.begin(), partOfHull.end(), partOfHull[0]), partOfHull.end());
		}
	}
}
