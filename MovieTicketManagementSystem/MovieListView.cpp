#include "MovieListView.h"


MovieListView::MovieListView(QListView* listView)
    : listView(listView)

{

    listModel = new QStringListModel(this);


    listView->setModel(listModel);

 
    setMoviesInListView();

}


MovieListView::~MovieListView()
{
    delete listModel;
}


void MovieListView::setMoviesInListView()
{
    QStringList moviesStringList;

    // Pobranie wszystkich filmów z bazy danych
    QList<Movie> movies = movieDatabase.getAllMovies();

    // Przechodzenie przez wszystkie filmy i dodawanie informacji o filmach do listy
    for (const Movie& movie : movies)
    {
        QString movieInfo = QString("%1 - %2 (%3 minutes)")
            .arg(movie.getTitle())
            .arg(movie.getDirector())
            .arg(movie.getDuration());

        moviesStringList.append(movieInfo);
    }

    listModel->setStringList(moviesStringList);

    // Aktualizacja widoku QListView
    listView->update();
}

