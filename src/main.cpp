#include "Convexia.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Convexia w;

    // Set the background color using a stylesheet
    w.setStyleSheet("background-color: rgb(34, 186, 219);"); // Change lightblue to your desired color

    w.show();
    return a.exec();
}
