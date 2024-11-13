#include "ObjWriter.h"
#include <fstream>
#include <iomanip>
#include <iostream>

vector<Point> uniqueVerticesList;
vector<Point> uniqueNormalsList;
map<Point, int> VerticeMap;
map<Point, int> NormalMap;


void ObjWriter::Write(const string& filename, const Triangulation& triangulation)
{
    ofstream outfile(filename);
    for (auto triangle : triangulation.Triangles)
    {
        findAndAddPoint(triangle.P1(), uniqueVerticesList, VerticeMap);
        findAndAddPoint(triangle.P2(), uniqueVerticesList, VerticeMap);
        findAndAddPoint(triangle.P3(), uniqueVerticesList, VerticeMap);
        findAndAddPoint(triangle.Normal(), uniqueNormalsList, NormalMap);
    }
    if (outfile.is_open())
    {

        for (Point pt : uniqueVerticesList)
        {
            outfile << fixed << setprecision(6)
                << formulateVertex(triangulation, pt);
        }
        for (Point normals : uniqueNormalsList)
        {
            outfile << fixed << setprecision(6)
                << formulateVertexNormal(triangulation, normals);
        }
        for (Triangle tri : triangulation.Triangles)
        {
            outfile << formulateFace(tri) << endl;
        }
    }
}


void ObjWriter::findAndAddPoint(Point point, vector<Point>& pointList, map<Point, int>& uniqueValueMap)
{
    auto pair = uniqueValueMap.find(point);
    if (pair == uniqueValueMap.end())
    {
        pointList.push_back(point);
        uniqueValueMap[point] = pointList.size() - 1;
    }
}

string ObjWriter::formulateVertex(Triangulation triangulation, Point point)
{
    double x = triangulation.UniqueNumbers[point.X()];
    double y = triangulation.UniqueNumbers[point.Y()];
    double z = triangulation.UniqueNumbers[point.Z()];

    return "v " + to_string(x) + " " + to_string(y) + " " + to_string(z) + "\n";
}

string ObjWriter::formulateVertexNormal(Triangulation triangulation, Point point)
{
    double x = triangulation.UniqueNumbers[point.X()];
    double y = triangulation.UniqueNumbers[point.Y()];
    double z = triangulation.UniqueNumbers[point.Z()];

    return "vn " + to_string(x) + " " + to_string(y) + " " + to_string(z) + "\n";
}

string ObjWriter::formulateFace(Triangle triangle)
{
    // v vt vn
    string new1 = to_string(VerticeMap[triangle.P1()] + 1) + "//" + to_string(NormalMap[triangle.Normal()] + 1)
        + " " + to_string(VerticeMap[triangle.P2()] + 1) + "//" + to_string(NormalMap[triangle.Normal()] + 1)
        + " " + to_string(VerticeMap[triangle.P3()] + 1) + "//" + to_string(NormalMap[triangle.Normal()] + 1);
    return "f " + new1;
}