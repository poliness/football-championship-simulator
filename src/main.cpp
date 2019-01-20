#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;

	w.setWindowTitle("Menu");
    w.show();

	w.otworzOknoPowitalne();

    return a.exec();
}
