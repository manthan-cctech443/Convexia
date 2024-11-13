#pragma once
#include<string>
#include<vector>
#include"Triangulation.h"

using namespace Geometry;
using namespace std;

class Writer
{
	virtual void Write(const string& filename, const Triangulation& trianglation) = 0;
};
