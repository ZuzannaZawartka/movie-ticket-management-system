#include "MainWindow.h"
#include "DatabaseManager.h"
#include "Movie.h"
#include "MovieDatabase.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
