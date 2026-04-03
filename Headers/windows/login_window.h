#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QMessageBox>
#include <QLabel>
#include "db/database_manager.h"


class login_window : public QWidget
{
    Q_OBJECT // required for Qt signal and slots
public:
    explicit login_window(QWidget* parent = nullptr);
protected:
    void resizeEvent(QResizeEvent* event);
private slots:
    void onLoginClicked();
private:
    QLineEdit* _username;
    QLineEdit* _password;
    QPushButton* _loginButton;
    QLabel* _bgImg;
    QString _bgPath;

private:
    bool verifyUser(const QString& username, const QString& password);
};

#endif // LOGIN_WINDOW_H
