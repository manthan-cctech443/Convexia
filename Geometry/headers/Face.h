#pragma once
#include "Dot.h"
#include "Vector.h"
#include <vector>

using namespace std;

namespace Geometry
{
    class Face
    {
    private:
        Dot d1;
        Dot d2;
        Dot d3;

    public:
        Face(Dot d1, Dot d2, Dot d3);
        ~Face();

        Dot D1();
        Dot D2();
        Dot D3();

        vector<Dot> Dots();
    };
}