#include "MovieDatabase.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <iostream>

using namespace std;


MovieDatabase::MovieDatabase()
{
    createTable();
}

bool MovieDatabase::createTable()
{
    QString query = "CREATE TABLE IF NOT EXISTS movies ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "director TEXT,"
        "type TEXT,"
        "duration INTEGER"
        ");";

    return executeQueryWithBindings(query, QVariantList());
}

bool MovieDatabase::addMovie(const Movie& movie)
{
    QString query = "INSERT INTO movies (title, director, type, duration) "
        "VALUES (?, ?, ?, ?);";

    QVariantList values;
    values << movie.getTitle() << movie.getDirector() << movie.getType() << movie.getDuration();

    return executeQueryWithBindings(query, values);
}


//TODO: this function does not work properly
bool MovieDatabase::updateMovie(const Movie& movie)
{
    int movieId = getMovieId(movie);

    if (movieId == -1) {
        return false;
    }

    QString query = "UPDATE movies SET title = ?, director = ?, type = ?, duration = ? WHERE id = ?;";

    QVariantList values;
    values << movie.getTitle() << movie.getDirector() << movie.getType() << movie.getDuration() << movieId;

    return executeQueryWithBindings(query, values);
}

bool MovieDatabase::deleteMovie(const Movie& movie)
{
    int movieId = getMovieId(movie);

    if (movieId == -1) {
        cout << "Movie not found." << endl;
        return false;
    }

    QString query = "DELETE FROM movies WHERE id = :id;"; // U¿yj nazwanego parametru ":id"

    QVariantList values;
    values << movieId;

    return executeQueryWithBindings(query, values);
}

bool MovieDatabase::isTableExists()
{
    QString query = "SELECT 1 FROM movies LIMIT 1;";
    return executeQueryWithBindings(query, QVariantList());
}

int MovieDatabase::getMovieId(const Movie& movie)
{
    QString query = "SELECT id FROM movies WHERE title = :title;";
    QVariantList values;
    values << movie.getTitle();

    QVariantList result = executeQueryWithBindingsAndReturn(query, values);

    if (!result.isEmpty()) {
        return result.first().toInt(); // Zwróæ pierwszy identyfikator filmu (jeœli istnieje)
    }
    else {
        qDebug() << "Movie not found.";
        return -1;
    }
}
