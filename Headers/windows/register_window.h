#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <iostream>
#include "db/database_manager.h"
#include <QMessageBox>

class register_window : public QWidget
{
    Q_OBJECT
public:
    explicit register_window(QWidget* parent = nullptr);
protected:
    void resizeEvent(QResizeEvent* event);
    void switchToLogin();
private slots:
    void onRegisterClicked();
signals:
    void switchToLoginRequested();
private:
    QLabel* _header;
    QLineEdit* _username;
    QLineEdit* _password;
    QLineEdit* _confirmPassword;
    QPushButton* _registerButton;
    QString _bgPath;
    QLabel* _bgImg;
    QLabel* _linkLabel;
};

#endif // REGISTER_WINDOW_H
