#include "Convexia.h"

#include "Triangulation.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QStatusBar>

using namespace Geometry;

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
}

void Convexia::onExportClick()
{
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
    layout->addWidget(customStatusBar, 2,0,1,4);

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
