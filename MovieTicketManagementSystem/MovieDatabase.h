#pragma once
#include "DatabaseManager.h"
#include "Movie.h"
#include <QStringList>
#include <QVariantList>
#include <QSqlQuery>
#include <QSqlRecord>
class MovieDatabase : public DatabaseManager
{
public:
    MovieDatabase();

    bool createTable();
    bool addMovie(const Movie& movie);
    bool deleteMovie(const Movie& movie);
    bool updateMovie(const Movie& oldMovie, const Movie& newMovie);
    bool movieExists(const Movie& movie);
    int getMovieId(const Movie& movie);
    QList<Movie> getAllMovies();
    bool isTableExists();
    
    Movie getMovieById(int id);
    Movie getMovieByTitle(const QString& title);


};