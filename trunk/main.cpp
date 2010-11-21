#include <QtGui/QApplication>
#include "dmwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    DmWindow w;
    w.show();
    return a.exec();
}
