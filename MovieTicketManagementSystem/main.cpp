#include "MainWindow.h"
#include "DatabaseManager.h"
#include "Movie.h"
#include "MovieDatabase.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MovieDatabase db;
    db.addMovie(Movie("The Shawshank Redemption", "Frank Darabont", "Drama", 142));
    db.addMovie(Movie("The Godfather2", "Francis Ford Coppola", "Crime", 175));

    w.show();
    return a.exec();
}
