QT += core gui widgets sql
INCLUDEPATH += Headers
CONFIG += c++17

TARGET = PasswordManager
TEMPLATE = app

HEADERS += \
    Headers/windows/database_manager.h \
    Headers/windows/login_window.h \
    Headers/windows/mainwindow.h \
    Headers/windows/register_window.h \
    Headers/db/database_manager.h

SOURCES += \
    Sources/main.cpp \
    Sources/windows/login_window.cpp \
    Sources/windows/mainwindow.cpp \
    Sources/windows/register_window.cpp \
    Sources/db/database_manager.cpp