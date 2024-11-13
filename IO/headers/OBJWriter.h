#pragma once
#include "Point.h"
#include "Writer.h"
#include "Triangulation.h"
#include <vector>
#include <map>

using namespace std;

namespace IO {
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
}