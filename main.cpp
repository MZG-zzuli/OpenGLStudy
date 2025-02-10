#include "glwidget.h"
#include"object.h"
#include <iostream>
#include <QApplication>
#include<thread>
#include<assimp/texture.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget w;
    w.show();

    const uchar* da=new uchar[100000000];
    aiTexture aa;
    
    aa.mWidth;
    aa.pcData;
    QImage img(da, 100, 100, QImage::Format_ARGB32);
    QOpenGLTexture texture(img);

    std::thread t([&]() {
        while (1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            w.update();
        }
        });
    t.detach();
    return a.exec();
}
