#include "MainWindow.h"
#include <QtWidgets/QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   
    // Utw�rz baz� danych film�w
    MovieDatabase movieDatabase;

    // Dodaj przyk�adowy film do bazy danych
    Movie exampleMovie("Example Title", "Example Director", "Example Type", 120);
    movieDatabase.addMovie(exampleMovie);


    w.show();
    return a.exec();
}
