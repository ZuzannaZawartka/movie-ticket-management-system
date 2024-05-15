#include "MovieListView.h"


MovieListView::MovieListView(QListView* listView)
    : listView(listView)  // Przypisanie wartoœci do pola listView w klasie MovieListView
{
    setMoviesInListView();

}


MovieListView::~MovieListView()
{
    delete listModel;
}


void MovieListView::setMoviesInListView()
{
    QStringList moviesStringList;
    QList<Movie> movies = movieDatabase.getAllMovies();

    for (const Movie& movie : movies)
    {
        QString movieInfo = QString("%1 - %2 (%3 minutes)")
            .arg(movie.getTitle())
            .arg(movie.getDirector())
            .arg(movie.getDuration());

        moviesStringList.append(movieInfo);
    }

    listModel->setStringList(moviesStringList);

    listView->setModel(listModel);
}
