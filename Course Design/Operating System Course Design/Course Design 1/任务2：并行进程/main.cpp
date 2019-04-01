#include "mainwindow.h"
#include <QApplication>

pid_t p1,p2,p3;

int main(int argc, char *argv[])
{
    int type;
    forking(type);

    QApplication a(argc, argv);
    MainWindow w(type);
    w.show();

    return a.exec();
}

void forking(int &type)
{
    if ((p1=fork())==0) {
        type=1;
        return;
    }
    else if ((p2=fork())==0) {
        type=2;
        return;
    }
    else if ((p3=fork())==0) {
        type=3;
        return;
    }
    else {
        type=0;
        return;
    }
}
