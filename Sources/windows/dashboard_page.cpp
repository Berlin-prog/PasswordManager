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

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(_welcomeLabel);
    _welcomeLabel->setGraphicsEffect(effect);

    QPropertyAnimation* fade = new QPropertyAnimation(effect, "opacity");
    fade->setDuration(700);
    fade->setStartValue(0);
    fade->setEndValue(1);
    fade->start(QAbstractAnimation::DeleteWhenStopped);
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
    QListWidget {
        background-color: #0F172A;
        color: white;
        border-radius: 10px;
        padding: 10px;
    }
    QListWidget::item {
        padding: 8px;
        border-radius: 6px;
    }
    QListWidget::item:hover {
        background-color: #1E293B;
    }
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
    QPushButton:pressed {
        background-color: #1E40AF;
        padding-top: 14px;
        padding-bottom: 10px;
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

    card->setAttribute(Qt::WA_Hover);
    card->installEventFilter(this);
    return card;

}

void dashboard_page::setUsername(const QString& username)
{
    _welcomeLabel->setText("Welcome back, " + username + " 👋");
}

bool dashboard_page::eventFilter(QObject* obj, QEvent* event)
{
    QWidget* card = qobject_cast<QWidget*>(obj);

    if (card)
    {
        if (event->type() == QEvent::Enter)
        {
            card->setStyleSheet(R"(
                background-color: #1E293B;
                border-radius: 15px;
                padding: 15px;
            )");
        }
        else if (event->type() == QEvent::Leave)
        {
            card->setStyleSheet(R"(
                background-color: #0F172A;
                border-radius: 15px;
                padding: 15px;
            )");
        }
    }

    return QWidget::eventFilter(obj, event);
}