#include "MainWindow.h"
#include <QtWidgets/QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   
    // Utwórz bazê danych filmów
    MovieDatabase movieDatabase;

    // Dodaj przyk³adowy film do bazy danych
    Movie exampleMovie("Example Title", "Example Director", "Example Type", 120);
    movieDatabase.addMovie(exampleMovie);


    w.show();
    return a.exec();
}
