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
    bool updateMovie(const Movie& movie);
    bool deleteMovie(const Movie& movie);
    int  getMovieIdByTitle(const Movie& movie);

private:
    bool isTableExists();
};