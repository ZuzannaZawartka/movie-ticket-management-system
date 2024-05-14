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
    // Tworzenie zapytania SQL z parametrem nazwanym
    QString query = "SELECT id FROM movies WHERE title = :title;";
    QVariantList values;
    values << movie.getTitle();

    // Wykonanie zapytania przy u¿yciu prepareQuery() z DatabaseManager
    QSqlQuery q = prepareQuery(query, values);

    // Sprawdzenie czy zapytanie siê powiod³o
    if (!q.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve movie ID!");
        return -1;
    }

    // Pobranie pierwszego wyniku zapytania (jeœli istnieje)
    if (q.next()) {
        return q.value(0).toInt(); // Zwróæ wartoœæ pierwszej kolumny (id)
    }
    else {
        QMessageBox::critical(nullptr, "Database Error", "Movie not found!");
        return -1;
    }
}

QList<Movie> MovieDatabase::getAllMovies()
{
    QList<Movie> movies;

    QSqlQuery query(db);

    // Pobieranie wszystkich filmów z bazy danych
    QString getAllMoviesQuery = "SELECT * FROM movies;";

    if (!query.exec(getAllMoviesQuery)) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to fetch movies from database!");
        return movies;
    }

    while (query.next()) {
        QString title = query.value(1).toString();
        QString director = query.value(2).toString();
        QString type = query.value(3).toString();
        int duration = query.value(4).toInt();

        Movie movie(title, director, type, duration);
        movies.append(movie);
    }

    return movies;
}

