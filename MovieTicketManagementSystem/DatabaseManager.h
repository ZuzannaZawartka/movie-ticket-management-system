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
    bool executeQueryWithBindings(const QString& query, const QVariantList& values);
    QSqlQuery prepareQuery(const QString& query, const QVariantList& values);
    

protected:
    QSqlDatabase db;
};

