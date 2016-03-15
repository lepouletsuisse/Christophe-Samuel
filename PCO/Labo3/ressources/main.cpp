#include "banditmanchot.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BanditManchot w;
    w.show();
    return a.exec();
}
