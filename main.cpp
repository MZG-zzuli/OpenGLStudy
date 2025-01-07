#include "glwidget.h"
#include <iostream>
#include <QApplication>
#include<thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget w;
    w.show();
    std::thread t([&]() {
        while (1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            w.update();
        }
        });
    t.detach();
    return a.exec();
}
