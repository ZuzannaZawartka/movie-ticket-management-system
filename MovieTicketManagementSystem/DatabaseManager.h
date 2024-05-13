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

protected:
    QSqlDatabase db;
};

