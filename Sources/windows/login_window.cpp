#include "windows/login_window.h"
login_window::login_window(QWidget* parent) : QWidget(parent)
{
    this->resize(1000, 700);

    // 🔹 Background image path
    _bgPath = "/home/berlin/Desktop/Password-Manager-UI/LoginPage/login_page_background.jpg";

    // 🎨 Global styles
    this->setStyleSheet(
        "QLineEdit {"
        "  border: 2px solid #ccc;"
        "  border-radius: 12px;"
        "  padding: 8px;"
        "  background-color: rgba(255,255,255,200);"
        "  font-size: 14px;"
        "}"

        "QLineEdit:focus {"
        "  border: 2px solid #4CAF50;"
        "}"

        "QPushButton {"
        "  background-color: #4CAF50;"
        "  color: white;"
        "  border-radius: 12px;"
        "  padding: 10px;"
        "  font-size: 14px;"
        "}"

        "QPushButton:hover {"
        "  background-color: #45a049;"
        "}"

        "QPushButton:pressed {"
        "  background-color: #3e8e41;"
        "}"
        );

    // 🖼️ Background label
    _bgImg = new QLabel(this);
    _bgImg->setGeometry(0, 0, this->width(), this->height());
    _bgImg->lower(); // send to back

    // 🔐 Input fields
    _username = new QLineEdit(this);
    _username->setPlaceholderText("Enter your username");

    _password = new QLineEdit(this);
    _password->setPlaceholderText("Enter your password");
    _password->setEchoMode(QLineEdit::Password);

    _loginButton = new QPushButton("Login", this);
    _loginButton->setDefault(true);
    connect(_username, &QLineEdit::returnPressed, this, &login_window::onLoginClicked);
    connect(_password, &QLineEdit::returnPressed, this, &login_window::onLoginClicked);

    // 📦 Form layout
    QVBoxLayout* formLayout = new QVBoxLayout();
    formLayout->addWidget(_username);
    formLayout->addWidget(_password);
    formLayout->addWidget(_loginButton);
    formLayout->setSpacing(15);

    // 🧊 Glass-style container
    QWidget* formWidget = new QWidget(this);
    formWidget->setLayout(formLayout);
    formWidget->setFixedWidth(300);
    formWidget->setStyleSheet(
        "background-color: rgba(0,0,0,120);"
        "border-radius: 15px;"
        "padding: 20px;"
        );

    // 📐 Main layout (centered)
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(formWidget, 0, Qt::AlignCenter);

    setLayout(mainLayout);

    // 🔗 Connect button
    connect(_loginButton, &QPushButton::clicked, this, &login_window::onLoginClicked);

    // 🔥 Set initial background
    QPixmap bg(_bgPath);
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    _bgImg->setPixmap(bg);
}

void login_window::onLoginClicked()
{
    QString username = _username->text();
    QString password = _password->text();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Username and password cannot be empty");
        return;
    }
    std::cout << username.toStdString() << " " << password.toStdString() << std::endl;
    _username->clear();
    _password->clear();
    if(!verifyUser(username, password))
    {
        qDebug() << "Invalid username or password!";
    } else
    {
        qDebug() << "Login Success!";
    }
}

void login_window::resizeEvent(QResizeEvent* event)
{
    QPixmap bg("/home/berlin/Desktop/Password-Manager-UI/LoginPage/login_page_background.jpg");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    _bgImg->setPixmap(bg);
    _bgImg->setGeometry(0, 0, this->width(), this->height());

    QWidget::resizeEvent(event);
}

bool login_window::verifyUser(const QString& username, const QString& password)
{
    auto db = DatabaseManager::instance().database();
    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if(!query.exec())
    {
        qDebug() << "Login query failed: " << query.lastError().text();
        return false;
    }

    if(query.next())
    {
        return true;
    } else {
        return false;
    }
}