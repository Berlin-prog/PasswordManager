#include "windows/mainwindow.h"
#include <QApplication>
#include "windows/login_window.h"
#include "db/database_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseManager::instance().openDB("passwords.db");
    DatabaseManager::instance().createTables();
    login_window login;
    login.show();

    return a.exec();
}
