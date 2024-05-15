#pragma once
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

class DatabaseManager
{
public:
    DatabaseManager();
    virtual ~DatabaseManager();

    bool isOpen() const;
    QSqlDatabase& database();
    bool executeQuery(const QString& queryStr, const QVariantList& values);
    QSqlQuery prepareQueryWithBindings(const QString& queryStr, const QVariantList& values);
    QSqlQuery prepareQueryWithBindings(const QString& queryStr);

protected:
    QSqlDatabase db;
};

