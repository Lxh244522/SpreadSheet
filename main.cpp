#include "mainwindow.h"
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw(10, 6);

    const QRect availableGeometry = QApplication::desktop()->availableGeometry(&mw);
    mw.resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
    mw.move((availableGeometry.width() - mw.width()) / 2,
            (availableGeometry.height() - mw.height()) / 2);

    mw.show();

    return a.exec();
}
