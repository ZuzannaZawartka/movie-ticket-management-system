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

QVariantList DatabaseManager::executeQueryWithBindingsAndReturn(const QString& query, const QVariantList& values)
{
    QVariantList result;

    if (!isOpen()) {
        qDebug() << "Database is not open!";
        return result;
    }

    QSqlQuery q(db);
    q.prepare(query);

    for (int i = 0; i < values.size(); ++i) {
        q.bindValue(i, values.at(i));
    }

    if (!q.exec()) {
        qDebug() << "Failed to execute query: ";
        return result;
    }

    while (q.next()) {
        result.append(q.value(0)); // Dodaj pierwsz¹ wartoœæ z ka¿dego wiersza do listy wyników
    }

    return result;
}
