#include "DatabaseManager.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>

const QString DatabasePath = "database.db";

DatabaseManager::DatabaseManager()
{

    db = QSqlDatabase::addDatabase("QSQLITE");

    // set database name
    db.setDatabaseName(DatabasePath);

    // open database
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to open database: ");
    }
    else {
        QMessageBox::information(nullptr, "Database Opened", "Database opened successfully");
    }
}

DatabaseManager::~DatabaseManager()
{
    db.close();
}

bool DatabaseManager::isOpen() const
{
    return db.isOpen();
}

QSqlDatabase& DatabaseManager::database()
{
    return db;
}

bool DatabaseManager::executeQuery(const QString& queryStr, const QVariantList& values)
{
    QSqlQuery query = prepareQueryWithBindings(queryStr, values);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to execute query: ");
        return false;
    }

    return true;
}


QSqlQuery DatabaseManager::prepareQueryWithBindings(const QString& queryStr, const QVariantList& values)
{
    QSqlQuery query(db);

    if (!isOpen()) {
        QMessageBox::critical(nullptr, "Database Error", "Database is not open!");
        return query;
    }

    query.prepare(queryStr);

    // Bindowanie wartoœci do zapytania
    for (int i = 0; i < values.size(); ++i) {
        query.bindValue(i, values.at(i));
    }

    return query;
}


QSqlQuery DatabaseManager::prepareQueryWithBindings(const QString& queryStr)
{
    QVariantList emptyValues;
    return prepareQueryWithBindings(queryStr, emptyValues);
}