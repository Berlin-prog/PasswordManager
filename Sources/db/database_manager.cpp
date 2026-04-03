#include "db/database_manager.h"
DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::openDB(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if(!db.open())
    {
        qDebug() << "Cannot open database: " << db.lastError() << "\n";
        return false;
    }
    qDebug() << "Database connected!\n";
    return true;
}

void DatabaseManager::createTables()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "username TEXT UNIQUE,"
                "password TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS vault ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "title TEXT,"
                "username TEXT,"
                "password TEXT,"
                "url TEXT,"
                "notes TEXT)");
}

QSqlDatabase& DatabaseManager::database()
{
    return db;
}