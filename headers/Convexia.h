#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QProgressBar>
#include<set>

#include "Triangulation.h"
#include "OpenGlWidget.h"
#include "GraphicsSynchronizer.h"

using namespace Geometry;

class Convexia : public QMainWindow
{
    Q_OBJECT

public:
    Convexia(QWidget* parent = nullptr);
    ~Convexia();

private slots:
    void onLoadClick();
    void onExportClick();

private:
    void setupUi();
    OpenGlWidget::Data convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation);
    Triangulation readFile(const QString& filePath);
    void writeFile(const QString& filePath, const Triangulation& triangulation);
    set<vector<double>> getUniquePoints(Triangulation& triangulation);

private:
    Triangulation triangulation;
    Triangulation outputTriangulation;

    QPushButton* loadFile;
    QPushButton* exportFile;

    QStatusBar* customStatusBar;

    QProgressBar* progressbar;

    OpenGlWidget* openglWidgetInput;
    OpenGlWidget* openglWidgetOutput;

    GraphicsSynchronizer* graphicsSynchronizer;

    QVector<GLfloat> vertices;

    // translation data
    QString inputFilePath;
    QString tempFilePath;
    QString outputFilePath;
};
