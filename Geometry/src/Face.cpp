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

bool Geometry::Face::operator==(const Face& other) const
{
	return (this->d1 == other.d1 && this->d2 == other.d2 && this->d3 == other.d3) ||
		(this->d1 == other.d1 && this->d2 == other.d3 && this->d3 == other.d2) || 
		(this->d1 == other.d2 && this->d2 == other.d3 && this->d3 == other.d1) || 
		(this->d1 == other.d2 && this->d2 == other.d1 && this->d3 == other.d3) || 
		(this->d1 == other.d3 && this->d2 == other.d1 && this->d3 == other.d2) || 
		(this->d1 == other.d3 && this->d2 == other.d2 && this->d3 == other.d1);
}

vector<Dot> Geometry::Face::Dots()
{
	std::vector<Dot> dots;
	dots.push_back(d1);
	dots.push_back(d2);
	dots.push_back(d3);
	return dots;
}
