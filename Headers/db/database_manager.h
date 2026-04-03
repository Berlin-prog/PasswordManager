#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>

class DatabaseManager
{
public:
    static DatabaseManager& instance();

    bool openDB(const QString& path);

    void createTables();

    QSqlDatabase& database();
private:
    DatabaseManager() {};
    QSqlDatabase db;
};

#endif // DATABASE_MANAGER_H
