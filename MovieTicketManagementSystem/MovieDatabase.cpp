#include "MovieDatabase.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>


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
    //if movie already exists, return false
    if (movieExists(movie)) {
        QMessageBox::critical(nullptr, "Database Error", "Movie already exists!");
        return false;
    }

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
        QMessageBox::critical(nullptr, "Database Error", "Movie not found!");
        return false;
    }

    QString query = "DELETE FROM movies WHERE id = :id;"; // U¿yj nazwanego parametru ":id"

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

Movie MovieDatabase::getMovieById(int id)
{
    QString queryStr = "SELECT * FROM movies WHERE id = :id;";
    QVariantList values;
    values << id;

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve movie by ID!");
        return Movie("", "", "", -1); //return empty movie object
    }

    if (query.next()) {
        QString title = query.value("title").toString();
        QString director = query.value("director").toString();
        QString type = query.value("type").toString();
        int duration = query.value("duration").toInt();

        return Movie(title, director, type, duration);
    }
    else {
        QMessageBox::critical(nullptr, "Database Error", "Movie not found!");
        return Movie("", "", "", -1); //return empty movie object
    }
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
    // check if the old movie exists
    int movieId = getMovieId(oldMovie);
    if (movieId == -1) {
        QMessageBox::critical(nullptr, "Database Error", "Old movie not found.");
        return false;
    }

    // check if the new movie already exists
    if (movieExists(newMovie)) {
        QMessageBox::critical(nullptr, "Database Error", "New movie already exists.");
        return false;
    }

    QString queryStr = "UPDATE movies SET title = :newTitle, director = :newDirector, type = :newType, duration = :newDuration WHERE id = :id;";
    QVariantList values;
    values << newMovie.getTitle() << newMovie.getDirector() << newMovie.getType() << newMovie.getDuration() << movieId;

    return executeQuery(queryStr, values);
}
Movie MovieDatabase::getMovieByTitle(const QString& title)
{
    QString queryStr = "SELECT * FROM movies WHERE title = :title;";
    QVariantList values;
    values << title;

    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve movie by title!");
        return Movie("", "", "", -1); // Return empty movie object
    }

    if (query.next()) {
        QString director = query.value("director").toString();
        QString type = query.value("type").toString();
        int duration = query.value("duration").toInt();

        return Movie(title, director, type, duration);
    }
    else {
        QMessageBox::critical(nullptr, "Database Error", "Movie with title " + title + " not found!");
        return Movie("", "", "", -1); // Return empty movie object
    }
}