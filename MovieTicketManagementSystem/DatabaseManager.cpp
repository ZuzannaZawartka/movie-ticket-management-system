#include "DatabaseManager.h"
#include <QMessageBox>

const QString DatabasePath = "database.sqlite";

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DatabasePath);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to open database: " + DatabasePath);
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

