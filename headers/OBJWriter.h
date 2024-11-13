#pragma once
#include "Writer.h"
#include <map>

using namespace std;
class ObjWriter : public Writer
{
public:
    void Write(const string& filename, const Triangulation& triangulation);

private:
    void findAndAddPoint(Point point, std::vector<Point>& pointList, std::map<Point, int>& uniqueValueMap);
    string formulateVertex(Triangulation triangulation, Point point);
    string formulateVertexNormal(Triangulation triangulation, Point point);
    string formulateFace(Triangle triangle);
};