#pragma once
#include "Triangle.h"
#include<vector>

namespace Geometry
{
    class Triangulation
    {
    public:
        Triangulation();
        ~Triangulation();

        vector<double> UniqueNumbers;
        vector<Triangle> Triangles;
    };
}