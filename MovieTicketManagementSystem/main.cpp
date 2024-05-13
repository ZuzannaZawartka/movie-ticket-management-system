#include "MainWindow.h"
#include "DatabaseManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DatabaseManager k;
    k.isOpen();
    w.show();
    return a.exec();
}
