#pragma once
#include<string>
#include<vector>
#include"Triangulation.h"

using namespace Geometry;

namespace IO {
	class Writer
	{
		virtual void Write(const string& filename, const Triangulation& trianglation) = 0;
	};
}
