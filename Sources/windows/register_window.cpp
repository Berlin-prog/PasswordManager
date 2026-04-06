#include "windows/register_window.h"
#include "windows/login_window.h"
register_window::register_window(QWidget* parent) : QWidget(parent)
{
    this->resize(1000, 700);
    _bgPath = "/home/berlin/Desktop/PasswordManager/images/login_register_page_background.jpg";

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

    _header = new QLabel("Sign Up", this);
    _header->setAlignment(Qt::AlignCenter);
    _header->setStyleSheet(
        "font-size: 32px;"
        "font-weight: bold;"
        "color: #FFFFFF;"
        "margin-top: 40px;"
        "margin-bottom: 40px;"
        );

    // 🔐 Input fields
    _username = new QLineEdit(this);
    _username->setPlaceholderText("Enter your username");

    _password = new QLineEdit(this);
    _password->setPlaceholderText("Enter your password");
    _password->setEchoMode(QLineEdit::Password);

    _confirmPassword = new QLineEdit(this);
    _confirmPassword->setPlaceholderText("Confirm password");
    _confirmPassword->setEchoMode(QLineEdit::Password);

    _registerButton = new QPushButton("Sign Up", this);
    _registerButton->setDefault(true);
    _registerButton->setAutoDefault(true);
    connect(_username, &QLineEdit::returnPressed, this, &register_window::onRegisterClicked);
    connect(_password, &QLineEdit::returnPressed, this, &register_window::onRegisterClicked);
    connect(_confirmPassword, &QLineEdit::returnPressed, this, &register_window::onRegisterClicked);
    _linkLabel = new QLabel(this);
    _linkLabel->setText("Already have an account? <a href='#'>Sign In</a>");
    _linkLabel->setAlignment(Qt::AlignCenter);
    _linkLabel->setStyleSheet(
        "QLabel { color: white; font-size: 14px; }"
        "QLabel a { color: #4CAF50; font-weight: bold; text-decoration: none; }"
        "QLabel a:hover { text-decoration: underline; }"
        );
    _linkLabel->setTextFormat(Qt::RichText);
    _linkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    _linkLabel->setOpenExternalLinks(false);

    // 📦 Form layout
    QVBoxLayout* formLayout = new QVBoxLayout();
    formLayout->addWidget(_username);
    formLayout->addWidget(_password);
    formLayout->addWidget(_confirmPassword);
    formLayout->addWidget(_registerButton);
    formLayout->addWidget(_linkLabel);
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
    mainLayout->addStretch();
    mainLayout->addWidget(_header, 0, Qt::AlignHCenter);
    mainLayout->addWidget(formWidget, 0, Qt::AlignCenter);
    mainLayout->addStretch();
    setLayout(mainLayout);

    // 🔗 Connect button
    connect(_registerButton, &QPushButton::clicked, this, &register_window::onRegisterClicked);
    connect(_linkLabel, &QLabel::linkActivated, this, &register_window::switchToLogin);
    // 🔥 Set initial background
    QPixmap bg(_bgPath);
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    _bgImg->setPixmap(bg);

}

void register_window::onRegisterClicked()
{
    QString username = _username->text();
    QString password = _password->text();
    QString confirmPassword = _confirmPassword->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields are required!");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match!");
        return;
    }

    // 🔑 Insert user into database
    auto db = DatabaseManager::instance().database();
    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // You can hash the password later

    if (!query.exec()) {
        // If insert fails (e.g., username already exists)
        QMessageBox::warning(this, "Error", "Failed to register user: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "User registered successfully!");
    _username->clear();
    _password->clear();
    _confirmPassword->clear();
}

void register_window::resizeEvent(QResizeEvent* event)
{
    QPixmap bg("/home/berlin/Desktop/PasswordManager/images/login_register_page_background.jpg");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    _bgImg->setPixmap(bg);
    _bgImg->setGeometry(0, 0, this->width(), this->height());
    QWidget::resizeEvent(event);
}

void register_window::switchToLogin()
{
    emit switchToLoginRequested();
}