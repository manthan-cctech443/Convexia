#include "Face.h"

using namespace Geometry;

Geometry::Face::Face(Dot d1, Dot d2, Dot d3)
	:d1(d1),d2(d2),d3(d3)
{
}

Geometry::Face::~Face()
{
}

Dot Geometry::Face::D1()
{
	return d1;
}

Dot Geometry::Face::D2()
{
	return d2;
}

Dot Geometry::Face::D3()
{
	return d3;
}

vector<Dot> Face::Dots()
{
	std::vector<Dot> dots;
	dots.push_back(d1);
	dots.push_back(d2);
	dots.push_back(d3);
	return dots;
}

// Compares two faces for equality by checking all permutations of their sides.
bool Geometry::Face::operator==(const Face& other) const
{
	return (d1 == other.d1 && d2 == other.d2 && d3 == other.d3) ||
		(d1 == other.d1 && d2 == other.d3 && d3 == other.d2) || 
		(d1 == other.d2 && d2 == other.d3 && d3 == other.d1) || 
		(d1 == other.d2 && d2 == other.d1 && d3 == other.d3) || 
		(d1 == other.d3 && d2 == other.d1 && d3 == other.d2) || 
		(d1 == other.d3 && d2 == other.d2 && d3 == other.d1);
}

