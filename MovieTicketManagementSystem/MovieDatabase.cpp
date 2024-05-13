#include "MovieDatabase.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

MovieDatabase::MovieDatabase(const QString& databasePath)
    : DatabaseManager(databasePath)
{
    // Upewnij siê, ¿e tabela jest utworzona podczas inicjalizacji
    createTable();
}

bool MovieDatabase::isTableExists()
{
    // SprawdŸ czy tabela "movies" istnieje w bazie danych
    QSqlQuery query(database());
    return query.exec("SELECT 1 FROM movies LIMIT 1;");
}

bool MovieDatabase::createTable()
{
    if (!isOpen()) {
        QMessageBox::critical(nullptr, "Database Error", "Database is not open!");
        return false;
    }

    if (isTableExists()) {
        QMessageBox::information(nullptr, "Table Exists", "Table 'movies' already exists.");
        return true;
    }

    // Utwórz tabelê "movies" w bazie danych
    QSqlQuery query(database());
    bool success = query.exec("CREATE TABLE movies ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "director TEXT,"
        "type TEXT,"
        "duration INTEGER"
        ");");

    if (!success) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to create table 'movies': " + query.lastError().text());
    }

    return success;
}

bool MovieDatabase::addMovie(const QString& title, const QString& director, const QString& type, int duration)
{
    if (!isOpen()) {
        QMessageBox::critical(nullptr, "Database Error", "Database is not open!");
        return false;
    }

    QSqlQuery query(database());
    query.prepare("INSERT INTO movies (title, director, type, duration) "
        "VALUES (?, ?, ?, ?);");
    query.addBindValue(title);
    query.addBindValue(director);
    query.addBindValue(type);
    query.addBindValue(duration);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to add movie: " + query.lastError().text());
        return false;
    }

    return true;
}

bool MovieDatabase::updateMovie(int id, const QString& title, const QString& director, const QString& type, int duration)
{
    if (!isOpen()) {
        QMessageBox::critical(nullptr, "Database Error", "Database is not open!");
        return false;
    }

    QSqlQuery query(database());
    query.prepare("UPDATE movies SET title = ?, director = ?, type = ?, duration = ? WHERE id = ?;");
    query.addBindValue(title);
    query.addBindValue(director);
    query.addBindValue(type);
    query.addBindValue(duration);
    query.addBindValue(id);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to update movie: " + query.lastError().text());
        return false;
    }

    return true;
}

bool MovieDatabase::deleteMovie(int id)
{
    if (!isOpen()) {
        QMessageBox::critical(nullptr, "Database Error", "Database is not open!");
        return false;
    }

    QSqlQuery query(database());
    query.prepare("DELETE FROM movies WHERE id = ?;");
    query.addBindValue(id);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to delete movie: " + query.lastError().text());
        return false;
    }

    return true;
}
