#include "windows/main_window.h"
#include <QApplication>
#include "windows/login_window.h"
#include "db/database_manager.h"
#include "windows/register_window.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseManager::instance().openDB("passwords.db");
    DatabaseManager::instance().createTables();
    // register_window registerPage;
    // login_window loginPage;
    // registerPage.show();

    // QObject::connect(&loginPage, &login_window::switchToRegisterRequested, [&](){
    //     loginPage.hide();
    //     registerPage.show();
    // });

    // QObject::connect(&registerPage, &register_window::switchToLoginRequested, [&](){
    //     registerPage.hide();
    //     loginPage.show();
    // });
    main_window x;
    x.show();
    return a.exec();
}
