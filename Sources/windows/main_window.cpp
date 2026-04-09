#include "windows/main_window.h"

main_window::main_window(QWidget* parent) : abstract_window(parent) {
    setupUI();
};

void main_window::setupUI()
{
    this->setMinimumSize(1200, 800);
    abstract_window::setupUI();

    _dashboard = new dashboard_page();

    _passwords = new passwords_page();
    _notes = new QWidget();
    _generator = new QWidget();
    _settings = new QWidget();

    _passwords->setStyleSheet("background-color: #020617;");
    _notes->setStyleSheet("background-color: #020617;");
    _generator->setStyleSheet("background-color: #020617;");
    _settings->setStyleSheet("background-color: #020617;");

    _content->addWidget(_dashboard);
    _content->addWidget(_passwords);
    _content->addWidget(_notes);
    _content->addWidget(_generator);
    _content->addWidget(_settings);

    connect(_dashboardBtn, &QPushButton::clicked, this, [this](){
        setActiveButton(_dashboardBtn);
        _content->setCurrentWidget(_dashboard);
    });

    connect(_passwordsBtn, &QPushButton::clicked, this, [this](){
        setActiveButton(_passwordsBtn);
        _content->setCurrentWidget(_passwords);
    });

    connect(_notesBtn, &QPushButton::clicked, this, [this](){
        setActiveButton(_notesBtn);
        _content->setCurrentWidget(_notes);
    });

    connect(_generatorBtn, &QPushButton::clicked, this, [this](){
        setActiveButton(_generatorBtn);
        _content->setCurrentWidget(_generator);
    });

    connect(_settingsBtn, &QPushButton::clicked, this, [this](){
        setActiveButton(_settingsBtn);
        _content->setCurrentWidget(_settings);
    });

    _content->setCurrentWidget(_dashboard);
}

void main_window::setUserData(const QString& username)
{
    setUsername(username);

    if(_dashboard)
    {
        _dashboard->setUsername(username);
    }
}