#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
class login_window : public QWidget
{
    Q_OBJECT // required for Qt signal and slots
public:
    explicit login_window(QWidget* parent = nullptr);

private slots:
    void onLoginClicked();
private:
    QLineEdit* _username;
    QLineEdit* _password;
    QPushButton* _loginButton;
};

#endif // LOGIN_WINDOW_H
