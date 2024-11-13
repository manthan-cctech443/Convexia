#pragma once
#include <string>
#include <vector>
#include "Writer.h"
#include "Triangle.h"
#include "Triangulation.h"

using namespace std;

namespace IO {
    class STLWriter : public Writer
    {
    public:
        void Write(const string& filename, const Triangulation& triangulation);

    private:
        string formulateText(Triangulation triangulation, Point point);
    };
}