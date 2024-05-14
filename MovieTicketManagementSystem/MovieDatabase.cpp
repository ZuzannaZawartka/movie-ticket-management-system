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
    int movieId = getMovieIdByTitle(movie);

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
    int movieId = getMovieIdByTitle(movie);

    if (movieId == -1) {
        cout << "Movie not found" << endl;
		return false;
	}
    
    QString query = "DELETE FROM movies WHERE id = ?;";

    QVariantList values;
    values << movie.getTitle();

    return executeQueryWithBindings(query, values);
}

bool MovieDatabase::isTableExists()
{
    QString query = "SELECT 1 FROM movies LIMIT 1;";
    return executeQueryWithBindings(query, QVariantList());
}

int MovieDatabase::getMovieIdByTitle(const Movie& movie) {
    QString query = "SELECT id FROM movies WHERE title = ?;";

    QVariantList values;
    values << movie.getTitle();

    QVariantList result = executeQueryWithBindingsAndReturn(query, values);

    if (!result.isEmpty()) {
        // Pobierz pierwszy element z listy wyników jako identyfikator filmu (jeœli jest)
        return result.first().toInt();
    }
    else {
        // Jeœli nie ma wyników, zwróæ -1 lub jak¹œ inn¹ wartoœæ oznaczaj¹c¹ brak filmu
        return -1;
    }
}