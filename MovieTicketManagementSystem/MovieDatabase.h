#pragma once
#include "DatabaseManager.h"
#include <QStringList>
#include <QVariantList>
#include <QSqlQuery>
#include <QSqlRecord>

class MovieDatabase : public DatabaseManager
{
public:
    MovieDatabase(const QString& databasePath = "movies_database.sqlite");

    bool createTable();
    bool addMovie(const QString& title, const QString& director, const QString& type, int duration);
    bool updateMovie(int id, const QString& title, const QString& director, const QString& type, int duration);
    bool deleteMovie(int id);

private:
    bool isTableExists();
};