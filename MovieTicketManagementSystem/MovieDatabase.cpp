#include "MovieDatabase.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <iostream>

using namespace std;

const QString DatabasePath = "database.db";

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

    return executeQuery(query, QVariantList());
}

bool MovieDatabase::addMovie(const Movie& movie)
{
    QString query = "INSERT INTO movies (title, director, type, duration) "
        "VALUES (?, ?, ?, ?);";

    QVariantList values;
    values << movie.getTitle() << movie.getDirector() << movie.getType() << movie.getDuration();

    return executeQuery(query, values);
}

bool MovieDatabase::deleteMovie(const Movie& movie)
{
    int movieId = getMovieId(movie);

    if (movieId == -1) {
        cout << "Movie not found." << endl;
        return false;
    }

    QString query = "DELETE FROM movies WHERE id = :id;"; // U�yj nazwanego parametru ":id"

    QVariantList values;
    values << movieId;

    return executeQuery(query, values);
}

bool MovieDatabase::movieExists(const Movie& movie)
{
    QString queryStr = "SELECT COUNT(*) FROM movies WHERE title = :title AND director = :director AND type = :type AND duration = :duration;";
    QVariantList values;
    values << movie.getTitle() << movie.getDirector() << movie.getType() << movie.getDuration();

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to check if movie exists!");
        return false;
    }

    query.next();
    int count = query.value(0).toInt(); //how many rows have been found

    return count != 0;
}

bool MovieDatabase::isTableExists()
{
    QString query = "SELECT 1 FROM movies LIMIT 1;";
    return executeQuery(query, QVariantList());
}

int MovieDatabase::getMovieId(const Movie& movie)
{
    QString queryStr = "SELECT id FROM movies WHERE title = :title AND director = :director AND type = :type AND duration = :duration;";
    QVariantList values;
    values << movie.getTitle() << movie.getDirector() << movie.getType() << movie.getDuration();

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve movie ID!");
        return -1;
    }

    if (query.next()) {
        return query.value(0).toInt(); // get the first column of the first row
    }
    else {
        QMessageBox::critical(nullptr, "Database Error", "Movie not found!");
        return -1;
    }
}

QList<Movie> MovieDatabase::getAllMovies()
{
    try {

    QList<Movie> movies;

    QString queryStr = "SELECT * FROM movies;";

    QSqlQuery query = prepareQueryWithBindings(queryStr);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve movies!");
        return movies;
    }

    while (query.next()) {
        QString title = query.value("title").toString();
        QString director = query.value("director").toString();
        QString type = query.value("type").toString();
        int duration = query.value("duration").toInt();

        Movie movie(title, director, type, duration);
        movies.append(movie);
    }

    return movies;

    }
    catch (const std::exception& e) {
            QMessageBox::critical(nullptr, "Database Error", QString("Error: ") + e.what());
    }
}


bool MovieDatabase::updateMovie(const Movie& oldMovie, const Movie& newMovie)
{
    if (!movieExists(oldMovie)) {
        QMessageBox::critical(nullptr, "Database Error", "Movie does not exist!");
        return false;
    }

    QString query = "UPDATE movies SET title = :newTitle, director = :newDirector, type = :newType, duration = :newDuration WHERE title = :oldTitle AND director = :oldDirector AND type = :oldType AND duration = :oldDuration;";
    QVariantList values;
    values << newMovie.getTitle() << newMovie.getDirector() << newMovie.getType() << newMovie.getDuration()
        << oldMovie.getTitle() << oldMovie.getDirector() << oldMovie.getType() << oldMovie.getDuration();

    return executeQuery(query, values);
}