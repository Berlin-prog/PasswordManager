#include "windows/passwords_page.h"
#include "windows/passwords_page.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QAbstractItemView>

#include "windows/passwords_page.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QAbstractItemView>

passwords_page::passwords_page(QWidget* parent) : QWidget(parent)
{
    setStyleSheet("background-color: #020617;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    // ===== TOP BAR =====
    QHBoxLayout* topLayout = new QHBoxLayout();

    _search = new QLineEdit();
    _search->setPlaceholderText("Search passwords...");
    _search->setStyleSheet(R"(
        QLineEdit {
            background-color: #0F172A;
            color: white;
            padding: 10px;
            border-radius: 10px;
        }
    )");

    _addBtn = new QPushButton("+ Add Password");
    _addBtn->setCursor(Qt::PointingHandCursor);
    _addBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #2563EB;
            color: white;
            padding: 10px 15px;
            border-radius: 10px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #1D4ED8;
        }
    )");

    topLayout->addWidget(_search);
    topLayout->addWidget(_addBtn);

    mainLayout->addLayout(topLayout);

    // ===== TABLE =====
    _table = new QTableWidget();

    _table->setColumnCount(3);
    _table->setRowCount(0);

    QStringList headers = {"Website", "Username", "Password"};
    _table->setHorizontalHeaderLabels(headers);

    _table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _table->horizontalHeader()->setMinimumHeight(45);

    _table->verticalHeader()->setVisible(false);
    _table->verticalHeader()->setDefaultSectionSize(50);

    _table->setShowGrid(false);
    _table->setAlternatingRowColors(true);

    // UX improvements
    _table->setSelectionBehavior(QAbstractItemView::SelectRows);
    _table->setSelectionMode(QAbstractItemView::SingleSelection);
    _table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _table->setFocusPolicy(Qt::NoFocus);
    _table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // ===== MODERN STYLE =====
    _table->setStyleSheet(R"(
        QTableWidget {
            background-color: #0F172A;
            color: white;
            border-radius: 14px;
            gridline-color: transparent;
            alternate-background-color: #111827;
            selection-background-color: #1E293B;
            padding: 6px;
        }

        QHeaderView::section {
            background-color: #020617;
            color: #94A3B8;
            padding: 12px;
            border: none;
            font-weight: 600;
            font-size: 13px;
        }

        QTableWidget::item {
            padding-left: 14px;
            padding-right: 14px;
        }

        QTableWidget::item:hover {
            background-color: #1E293B;
        }
    )");

    mainLayout->addWidget(_table);

    // ===== LOAD DATA =====
    loadFakeData();
}

void passwords_page::loadFakeData()
{
    struct Data {
        QString site;
        QString user;
        QString pass;
    };

    QList<Data> list = {
        {"Gmail", "Berlin070793", "Berli+n070793"},
        {"GitHub", "devUser", "qwerty123"},
        {"Facebook", "john_doe", "abc123"},
        {"Twitter", "tweetGuy", "pass777"}
    };

    _table->setRowCount(list.size());

    for (int i = 0; i < list.size(); ++i)
    {
        QTableWidgetItem* siteItem = new QTableWidgetItem(list[i].site);
        QTableWidgetItem* userItem = new QTableWidgetItem(list[i].user);
        QTableWidgetItem* passItem = new QTableWidgetItem(list[i].pass);

        // ✅ alignment AFTER creation
        siteItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        userItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        passItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignCenter);

        _table->setItem(i, 0, siteItem);
        _table->setItem(i, 1, userItem);
        _table->setItem(i, 2, passItem);
    }
}