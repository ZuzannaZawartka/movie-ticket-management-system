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


    query.prepare(queryStr);

    if (queryStr.isEmpty()) {
        QMessageBox::critical(nullptr, "Query Error", "Empty SQL query!");
        return query;
    }

    if (!query.prepare(queryStr)) {
        QMessageBox::critical(nullptr, "Query Error", "Failed to prepare SQL query!");
        return query;
    }

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