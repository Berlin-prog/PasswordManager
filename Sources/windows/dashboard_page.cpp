#include "windows/dashboard_page.h"

#include "dashboard_page.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

dashboard_page::dashboard_page(QWidget* parent) : QWidget(parent)
{
    setStyleSheet("background-color: #020617;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(25);

    // ===== 1. Welcome =====
    _welcomeLabel = new QLabel("Welcome back 👋");
    _welcomeLabel->setStyleSheet(R"(
        color: white;
        font-size: 26px;
        font-weight: bold;
    )");

    mainLayout->addWidget(_welcomeLabel);

    // ===== 2. Stats =====
    QHBoxLayout* statsLayout = new QHBoxLayout();
    statsLayout->setSpacing(15);

    statsLayout->addWidget(createCard("Total Passwords", "24"));
    statsLayout->addWidget(createCard("Weak Passwords", "3"));
    statsLayout->addWidget(createCard("Security Score", "78%"));

    mainLayout->addLayout(statsLayout);

    // ===== 3. Activity =====
    QLabel* activityTitle = new QLabel("Recent Activity");
    activityTitle->setStyleSheet("color: white; font-size: 18px;");

    mainLayout->addWidget(activityTitle);

    QListWidget* activityList = new QListWidget();
    activityList->addItem("Added Gmail");
    activityList->addItem("Updated Facebook");
    activityList->addItem("Deleted Twitter");

    activityList->setStyleSheet(R"(
        background-color: #0F172A;
        color: white;
        border-radius: 10px;
        padding: 10px;
    )");

    mainLayout->addWidget(activityList);

    // ===== 4. Button =====
    QPushButton* addBtn = new QPushButton("+ Add Password");
    addBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #2563EB;
            color: white;
            padding: 12px;
            border-radius: 10px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #1D4ED8;
        }
    )");

    mainLayout->addWidget(addBtn);
    mainLayout->addStretch();
}

QWidget* dashboard_page::createCard(const QString& title, const QString& value)
{
    QWidget* card = new QWidget();
    card->setStyleSheet(R"(
        background-color: #0F172A;
        border-radius: 15px;
        padding: 15px;
    )");
    QVBoxLayout* layout = new QVBoxLayout(card);
    QLabel* t = new QLabel(title);
    t->setStyleSheet("color: #94A3B8;");
    QLabel* v = new QLabel(value);
    v->setStyleSheet("color: white; font-size: 20px; font-weight: bold;");

    layout->addWidget(t);
    layout->addWidget(v);
    return card;

}

void dashboard_page::setUsername(const QString& username)
{
    _welcomeLabel->setText("Welcome back, " + username + " 👋");
}