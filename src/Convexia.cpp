#include "Convexia.h"
#include "STLReader.h"
#include "OBJReader.h"
#include "QuickHull.h"
#include "Operations.h"
#include "Face.h"
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
}

Convexia::~Convexia()
{
}

void Convexia::onLoadClick()
{
    customStatusBar->showMessage("Select a file .");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.stl *.obj)"));

    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        triangulation = readFile(inputFilePath);
        customStatusBar->showMessage("Loading file and Generating Convex Hull !.");
        OpenGlWidget::Data data = convertTrianglulationToGraphicsObject(triangulation);
        openglWidgetInput->addObject(data);

        QuickHull quickHull;
        vector<Face> output = quickHull.implementQuickHull(convertGraphicsObjectToPoints(data));

        openglWidgetInput->addObject(convertFacesToGraphicsObject(output));
        openglWidgetOutput->addObject(convertFacesToGraphicsObject(output));
        customStatusBar->showMessage("Convex Hull Generated!.");
    }

}


void Convexia::setupUi()
{
    loadFile = new QPushButton("Load File", this);
    openglWidgetInput = new OpenGlWidget(this);
    openglWidgetOutput = new OpenGlWidget(this);
    progressbar = new QProgressBar(this);
    customStatusBar = new QStatusBar(this);
    graphicsSynchronizer = new GraphicsSynchronizer(openglWidgetInput, openglWidgetOutput);

    loadFile->setStyleSheet(
        "QPushButton {"
        "    background-color: rgb(24, 45, 118);"
        "    color: white;"
        "    border: 2px solid rgb(0, 0, 0);"
        "    border-radius: 10px;" // Makes the corners rounded
        "    padding: 5px;"
        "    font: bold 14px 'Open Sanst';"
        "}"
        "QPushButton:hover {"
        "    background-color: rgb(34, 65, 138);"
        "}"
    );

    progressbar->setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid black;"
        "    border-radius: 10px;" // Rounded corners
        "    text-align: center;"
        "    background: lightgray;"
        "}"
        "QProgressBar::chunk {"
        "    border-radius: 10px;" // Rounded corners for the progress chunk
        "    background: rgb(17,160,23);"
        "}"
    );

    customStatusBar->setStyleSheet(
        "QStatusBar {"
        "font: bold 14px 'Arial'; "
        "}"
    );

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(loadFile, 0, 0);
    layout->addWidget(progressbar, 0, 1);
    layout->addWidget(openglWidgetInput, 1, 0);
    layout->addWidget(openglWidgetOutput, 1, 1);
    layout->addWidget(customStatusBar, 2, 0);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
    customStatusBar->setFixedHeight(30);

    customStatusBar->showMessage("Welcome to CONVEXIA  APP ! Load your file ....");
}

OpenGlWidget::Data Convexia::convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation)
{
    OpenGlWidget::Data data;
    int count = 1;
    for (Triangle triangle : inTriangulation.triangles)
    {
        vector<Point> pts = triangle.Points();
        Point normal = triangle.Normal();
        for (size_t i = 0; i < pts.size(); i++)
        {
            data.vertices.push_back(inTriangulation.uniqueNumbers[pts[i].X()]);
            data.vertices.push_back(inTriangulation.uniqueNumbers[pts[i].Y()]);
            data.vertices.push_back(inTriangulation.uniqueNumbers[pts[i].Z()]);
            data.normals.push_back(inTriangulation.uniqueNumbers[normal.X()]);
            data.normals.push_back(inTriangulation.uniqueNumbers[normal.Y()]);
            data.normals.push_back(inTriangulation.uniqueNumbers[normal.Z()]);
            data.colors.push_back(1.0);
            data.colors.push_back(0.608);
            data.colors.push_back(0.0);
        }

        progressbar->setValue(count);
        count++;
    }
    data.drawStyle = OpenGlWidget::DrawStyle::TRIANGLES;
    return data;
}

vector<Dot> Convexia::convertGraphicsObjectToPoints(const OpenGlWidget::Data& data)
{
    set<Dot> PointCloudSet;
    for (int i = 0; i < data.vertices.size(); i = i + 3) {
        Dot d(static_cast<double>(data.vertices[i]), static_cast<double>(data.vertices[i + 1]), static_cast<double>(data.vertices[i + 2]));

        PointCloudSet.insert(d);
    }
    vector<Dot>PointCloud(PointCloudSet.begin(), PointCloudSet.end());
    return  PointCloud;
}

OpenGlWidget::Data Convexia::convertFacesToGraphicsObject(const vector<Face> hull)
{
    OpenGlWidget::Data data1;
    for (Face face : hull) {
        vector<Dot> dts = face.Dots();

        for (size_t i = 0; i < dts.size(); i++)
        {
            data1.vertices.push_back(static_cast<GLfloat>(dts[i].X()));
            data1.vertices.push_back(static_cast<GLfloat>(dts[i].Y()));
            data1.vertices.push_back(static_cast<GLfloat>(dts[i].Z()));
            data1.colors.push_back(0.0f);
            data1.colors.push_back(0.0f);
            data1.colors.push_back(0.0f);
        }
    }
    data1.drawStyle = OpenGlWidget::DrawStyle::LINES;
    return data1;
}


Triangulation Convexia::readFile(const QString& filePath)
{
    Triangulation triangulation;
    if (filePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        STLReader reader;
        reader.read(filePath.toStdString(), triangulation);
        progressbar->setRange(0, triangulation.triangles.size());
    }
    else if (filePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        OBJReader reader;
        reader.read(filePath.toStdString(), triangulation);
        progressbar->setRange(0, triangulation.triangles.size());
    }

    return triangulation;
}