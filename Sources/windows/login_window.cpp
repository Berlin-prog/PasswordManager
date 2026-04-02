#include "windows/login_window.h"
login_window::login_window(QWidget* parent) : QWidget(parent)
{
    _username = new QLineEdit(this);
    _username->setPlaceholderText("Enter your username");

    _password = new QLineEdit(this);
    _password->setPlaceholderText("Enter your password");
    _password->setEchoMode(QLineEdit::Password);

    _loginButton = new QPushButton("Login", this);

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(_username);
    layout->addWidget(_password);
    layout->addWidget(_loginButton);

    setLayout(layout);

    connect(_loginButton, &QPushButton::clicked, this, &login_window::onLoginClicked);
}

void login_window::onLoginClicked()
{
    QString username = _username->text();
    QString password = _password->text();
    std::cout << username.toStdString() << " " << password.toStdString() << std::endl;
    _username->clear();
    _password->clear();
}