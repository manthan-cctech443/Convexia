#pragma once
#include<string>
#include "Triangulation.h"

using namespace Geometry;

namespace IO {
	class Reader
	{
		virtual void read(const std::string& fileName, Triangulation& triangulation) = 0;
	};
}
