#include "mainscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //添加了一行无用的注释
    QApplication a(argc, argv);
    MainScene w;
    w.show();

    return a.exec();
}
