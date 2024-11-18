#include "Convexia.h"
#include "Dot.h"
#include "Triangulation.h"
#include "STLReader.h"
#include "STLWriter.h"
#include "OBJReader.h"
#include "OBJWriter.h"
#include "QuickHull.h"
#include "Operations.h"
#include <iostream>
#include <set>
#include <QFileDialog>
#include <QGridLayout>
#include <QStatusBar>
using namespace Geometry;
using namespace Algorithm;
using namespace std;

Convexia::Convexia(QWidget* parent) : QMainWindow(parent)
{
    setupUi();

    connect(loadFile, &QPushButton::clicked, this, &Convexia::onLoadClick);
    connect(exportFile, &QPushButton::clicked, this, &Convexia::onExportClick);
}

Convexia::~Convexia()
{
}

void Convexia::onLoadClick()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.stl *.obj)"));

    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        triangulation = readFile(inputFilePath);
        OpenGlWidget::Data data = convertTrianglulationToGraphicsObject(triangulation);
        openglWidgetInput->setData(data);
        set<Dot> PointCloudSet;
        for (int i = 0; i < data.vertices.size(); i = i + 3) {
            Dot d(static_cast<double>(data.vertices[i]), static_cast<double>(data.vertices[i + 1]), static_cast<double>(data.vertices[i + 2]));

            PointCloudSet.insert(d);
        }
        vector<Dot>PointCloud(PointCloudSet.begin(), PointCloudSet.end());
        vector<Face> output = quickHull(PointCloud);
        OpenGlWidget::Data data1;
        for (Face f : output) {
            data1.vertices.push_back(static_cast<GLfloat>(f.D1().X()));
            data1.vertices.push_back(static_cast<GLfloat>(f.D1().Y()));
            data1.vertices.push_back(static_cast<GLfloat>(f.D1().Z()));
            data1.vertices.push_back(static_cast<GLfloat>(f.D2().X()));
            data1.vertices.push_back(static_cast<GLfloat>(f.D2().Y()));
            data1.vertices.push_back(static_cast<GLfloat>(f.D2().Z()));
            data1.vertices.push_back(static_cast<GLfloat>(f.D3().X()));
            data1.vertices.push_back(static_cast<GLfloat>(f.D3().Y()));
            data1.vertices.push_back(static_cast<GLfloat>(f.D3().Z()));

            GVector nor = getNormal(f.D1(), f.D2(), f.D3());

            for (int i = 0;i < 3;i++) {
                data1.normals.push_back(static_cast<GLfloat>(nor.x));
                data1.normals.push_back(static_cast<GLfloat>(nor.y));
                data1.normals.push_back(static_cast<GLfloat>(nor.z));
            }
        }
        openglWidgetOutput->setData(data1);
    }

}

void Convexia::onExportClick()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", inputFilePath.endsWith(".stl", Qt::CaseInsensitive) ? tr("files (*.obj)") : tr("files (*.stl)"));
    if (!fileName.isEmpty())
    {
        writeFile(fileName, outputTriangulation);
    }
}

void Convexia::setupUi()
{
    loadFile = new QPushButton("Load File", this);
    exportFile = new QPushButton("Export", this);
    openglWidgetInput = new OpenGlWidget(this);
    openglWidgetOutput = new OpenGlWidget(this);
    progressbar = new QProgressBar(this);
    customStatusBar = new QStatusBar(this);
    graphicsSynchronizer = new GraphicsSynchronizer(openglWidgetInput, openglWidgetOutput);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(loadFile, 0, 0);
    layout->addWidget(progressbar, 0, 1, 1, 2);
    layout->addWidget(exportFile, 0, 3);
    layout->addWidget(openglWidgetInput, 1,0,1,2);
    layout->addWidget(openglWidgetOutput, 1,2,1,2);
    layout->addWidget(customStatusBar, 2,0);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
    customStatusBar->setFixedHeight(30);

    customStatusBar->showMessage("Welcome to CONVEXIA APP ! Load your file.");
}

OpenGlWidget::Data Convexia::convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation)
{
    OpenGlWidget::Data data;
    int count = 1;
    for (Triangle triangle : inTriangulation.Triangles)
    {
        for (Point point : triangle.Points())
        {
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Z()]);
        }

        Point normal = triangle.Normal();

        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Z()]);
        }
        progressbar->setValue(count);
        count++;
    }
    return data;
}


Triangulation Convexia::readFile(const QString& filePath)
{
    Triangulation triangulation;
    if (filePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        STLReader reader;
        reader.read(filePath.toStdString(), triangulation);
        progressbar->setRange(0, triangulation.Triangles.size());
    }
    else if (filePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        OBJReader reader;
        reader.read(filePath.toStdString(), triangulation);
        progressbar->setRange(0, triangulation.Triangles.size());
    }

    return triangulation;
}

void Convexia::writeFile(const QString& filePath, const Triangulation& triangulation)
{
    if (filePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        STLWriter writer;
        writer.Write(filePath.toStdString(), triangulation);
    }
    else if (filePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        ObjWriter writer;
        writer.Write(filePath.toStdString(), triangulation);
    }
}
