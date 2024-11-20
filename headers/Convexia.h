#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QProgressBar>
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


private:
    void setupUi();
    OpenGlWidget::Data convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation);
    Triangulation readFile(const QString& filePath);

private:
    Triangulation triangulation;
    Triangulation outputTriangulation;

    QPushButton* loadFile;

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
