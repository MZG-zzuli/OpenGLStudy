#include "glwidget.h"
#include <iostream>
#include <QApplication>
#include<thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget w;
    w.show();
    return a.exec();
}
