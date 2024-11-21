#pragma once
#include "Dot.h"
#include "GVector.h"
#include <vector>

using namespace std;

namespace Geometry
{
    class Face
    {

    public:

        Face(Dot d1, Dot d2, Dot d3);
        ~Face();

        Dot D1();
        Dot D2();
        Dot D3();

        bool operator==(const Face& other) const;  

    private:

        Dot d1;
        Dot d2;
        Dot d3;
    };
}