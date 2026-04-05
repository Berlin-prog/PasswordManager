#include "windows/main_window.h"

main_window::main_window(QWidget* parent) : QWidget(parent)
{
    setMinimumSize(1200, 800);
    setupUI();
}

void main_window::setupUI()
{
    // MAIN LAYOUT
    _mainLayout = new QHBoxLayout(this);
    _mainLayout->setContentsMargins(0, 0, 0, 0);
    _mainLayout->setSpacing(0);

    // SIDEBAR
    _sidebar = new QWidget();
    _sidebar->setFixedWidth(250);

    _sidebar->setStyleSheet(R"(
        background-color: #0F172A;
    )");

    _sidebarLayout = new QVBoxLayout(_sidebar);
    _sidebarLayout->setContentsMargins(20, 20, 20, 20);
    _sidebarLayout->setSpacing(15);

    // ===== TOP TITLE =====
    QLabel* title = new QLabel("Password Manager");
    title->setStyleSheet(R"(
        font-size: 20px;
        font-weight: bold;
        color: white;
    )");

    _sidebarLayout->addWidget(title);
    _sidebarLayout->addSpacing(10);

    // ===== BUTTON STYLE =====
    _btnStyle = R"(
        QPushButton {
            text-align: left;
            padding: 12px;
            border: none;
            color: #CBD5E1;
            background-color: transparent;
            border-radius: 10px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #1E293B;
            color: white;
        }
    )";

    // ===== ACTIVE BUTTON STYLE (Dashboard) =====
    _activeStyle = R"(
        QPushButton {
            text-align: left;
            padding: 12px;
            border: none;
            color: white;
            background-color: #2563EB;
            border-radius: 10px;
            font-size: 14px;
        }
    )";

    _dashboardBtn = new QPushButton("Dashboard");
    _passwordsBtn = new QPushButton("Passwords");
    _notesBtn = new QPushButton("Secure Notes");
    _generatorBtn = new QPushButton("Generator");
    _settingsBtn = new QPushButton("Settings");

    _dashboardBtn->setStyleSheet(_activeStyle);
    _passwordsBtn->setStyleSheet(_btnStyle);
    _notesBtn->setStyleSheet(_btnStyle);
    _generatorBtn->setStyleSheet(_btnStyle);
    _settingsBtn->setStyleSheet(_btnStyle);

    _sidebarLayout->addWidget(_dashboardBtn);
    _sidebarLayout->addWidget(_passwordsBtn);
    _sidebarLayout->addWidget(_notesBtn);
    _sidebarLayout->addWidget(_generatorBtn);
    _sidebarLayout->addWidget(_settingsBtn);

    _sidebarLayout->addStretch();


    _username = new QLabel("John Doe");
    _username->setStyleSheet("color: white; font-weight: bold;");

    _logoutBtn = new QPushButton("Log out");
    _logoutBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #DC2626;
            color: white;
            border-radius: 8px;
            padding: 8px;
        }
        QPushButton:hover {
            background-color: #B91C1C;
        }
    )");

    _sidebarLayout->addWidget(_username);
    _sidebarLayout->addSpacing(10);
    _sidebarLayout->addWidget(_logoutBtn);

    QWidget* content = new QWidget();
    content->setStyleSheet("background-color: #020617;");

    // ADD TO MAIN
    _mainLayout->addWidget(_sidebar);
    _mainLayout->addWidget(content);
}