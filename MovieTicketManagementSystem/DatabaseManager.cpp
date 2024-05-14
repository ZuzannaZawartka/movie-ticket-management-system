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

bool DatabaseManager::executeQueryWithBindings(const QString& query, const QVariantList& values)
{
    if (!isOpen()) {
        QMessageBox::critical(nullptr, "Database Error", "Database is not open!");
        return false;
    }

    QSqlQuery q(db);
    q.prepare(query);

    for (int i = 0; i < values.size(); ++i) {
        q.bindValue(i, values.at(i));
    }

    if (!q.exec()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to execute query: ");
        return false;
    }

    return true;
}

QSqlQuery DatabaseManager::prepareQuery(const QString& query, const QVariantList& values)
{
    QSqlQuery q(db);

    if (!isOpen()) {
        QMessageBox::critical(nullptr, "Database Error", "Database is not open!");
        return q;
    }

    q.prepare(query);

    // Bindowanie wartoœci do zapytania
    for (int i = 0; i < values.size(); ++i) {
        q.bindValue(i, values.at(i));
    }

    return q;
}
