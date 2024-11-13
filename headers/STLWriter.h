#pragma once
#include "Writer.h"

using namespace std;

class STLWriter : public Writer
{
public:
    void Write(const string& filename, const Triangulation& triangulation);

private:
    string formulateText(Triangulation triangulation, Point point);
};