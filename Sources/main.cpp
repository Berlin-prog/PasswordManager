#include "windows/mainwindow.h"
#include <QApplication>
#include "windows/login_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    login_window login;
    login.show();

    return a.exec();
}
