//main.cpp
#include "Undupify.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Undupify w;
    w.show();
    return a.exec();
}
