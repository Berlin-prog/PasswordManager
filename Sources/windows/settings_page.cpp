#include "windows/settings_page.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QFrame>

// ================= CONSTRUCTOR =================

settings_page::settings_page(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

// ================= UI =================

void settings_page::setupUI()
{
    setStyleSheet("background-color: #020617;");

    QVBoxLayout* main = new QVBoxLayout(this);
    main->setContentsMargins(40, 40, 40, 40);
    main->setSpacing(25);

    QLabel* title = new QLabel("Settings");
    title->setStyleSheet("color: white; font-size: 24px; font-weight: bold;");
    main->addWidget(title);

    // ===== COMMON STYLES =====
    QString cardStyle = R"(
        QFrame {
            background-color: #0F172A;
            border-radius: 16px;
        }
    )";

    QString labelStyle = "color: white; font-size: 14px;";
    QString subLabelStyle = "color: #94A3B8; font-size: 12px;";

    QString comboStyle = R"(
        QComboBox {
            background-color: #1E293B;
            color: white;
            padding: 6px;
            border-radius: 8px;
        }
    )";

    QString toggleStyle = R"(
        QCheckBox {
            color: white;
            spacing: 10px;
        }
        QCheckBox::indicator {
            width: 40px;
            height: 20px;
        }
        QCheckBox::indicator:unchecked {
            background-color: #334155;
            border-radius: 10px;
        }
        QCheckBox::indicator:checked {
            background-color: #2563EB;
            border-radius: 10px;
        }
    )";

    // ================= SECURITY =================
    QFrame* security = new QFrame();
    security->setStyleSheet(cardStyle);

    QVBoxLayout* secLayout = new QVBoxLayout(security);
    secLayout->setContentsMargins(20, 20, 20, 20);
    secLayout->setSpacing(15);

    QLabel* secTitle = new QLabel("Security");
    secTitle->setStyleSheet("color: white; font-weight: bold; font-size: 16px;");

    // Auto lock
    QHBoxLayout* autoLockLayout = new QHBoxLayout();

    QVBoxLayout* autoLockText = new QVBoxLayout();
    QLabel* autoLockLabel = new QLabel("Auto-lock");
    autoLockLabel->setStyleSheet(labelStyle);

    QLabel* autoLockDesc = new QLabel("Lock app after inactivity");
    autoLockDesc->setStyleSheet(subLabelStyle);

    autoLockText->addWidget(autoLockLabel);
    autoLockText->addWidget(autoLockDesc);

    _autoLock = new QComboBox();
    _autoLock->addItems({"Never", "1 min", "5 min", "10 min"});
    _autoLock->setStyleSheet(comboStyle);

    autoLockLayout->addLayout(autoLockText);
    autoLockLayout->addStretch();
    autoLockLayout->addWidget(_autoLock);

    // Clear clipboard
    QHBoxLayout* clipboardLayout = new QHBoxLayout();

    QVBoxLayout* clipboardText = new QVBoxLayout();
    QLabel* clipLabel = new QLabel("Clear clipboard");
    clipLabel->setStyleSheet(labelStyle);

    QLabel* clipDesc = new QLabel("Auto clear copied passwords");
    clipDesc->setStyleSheet(subLabelStyle);

    clipboardText->addWidget(clipLabel);
    clipboardText->addWidget(clipDesc);

    _clearClipboard = new QCheckBox();
    _clearClipboard->setStyleSheet(toggleStyle);

    clipboardLayout->addLayout(clipboardText);
    clipboardLayout->addStretch();
    clipboardLayout->addWidget(_clearClipboard);

    secLayout->addWidget(secTitle);
    secLayout->addLayout(autoLockLayout);
    secLayout->addLayout(clipboardLayout);

    main->addWidget(security);

    // ================= APPEARANCE =================
    QFrame* appearance = new QFrame();
    appearance->setStyleSheet(cardStyle);

    QVBoxLayout* appLayout = new QVBoxLayout(appearance);
    appLayout->setContentsMargins(20, 20, 20, 20);

    QLabel* appTitle = new QLabel("Appearance");
    appTitle->setStyleSheet("color: white; font-weight: bold; font-size: 16px;");

    QHBoxLayout* themeLayout = new QHBoxLayout();

    QVBoxLayout* themeText = new QVBoxLayout();
    QLabel* themeLabel = new QLabel("Theme");
    themeLabel->setStyleSheet(labelStyle);

    QLabel* themeDesc = new QLabel("Choose app theme");
    themeDesc->setStyleSheet(subLabelStyle);

    themeText->addWidget(themeLabel);
    themeText->addWidget(themeDesc);

    _theme = new QComboBox();
    _theme->addItems({"Dark", "Light"});
    _theme->setStyleSheet(comboStyle);

    themeLayout->addLayout(themeText);
    themeLayout->addStretch();
    themeLayout->addWidget(_theme);

    appLayout->addWidget(appTitle);
    appLayout->addLayout(themeLayout);

    main->addWidget(appearance);

    // ================= BEHAVIOR =================
    QFrame* behavior = new QFrame();
    behavior->setStyleSheet(cardStyle);

    QVBoxLayout* behLayout = new QVBoxLayout(behavior);
    behLayout->setContentsMargins(20, 20, 20, 20);

    QLabel* behTitle = new QLabel("Behavior");
    behTitle->setStyleSheet("color: white; font-weight: bold; font-size: 16px;");

    // Startup
    QHBoxLayout* startupLayout = new QHBoxLayout();

    QVBoxLayout* startupText = new QVBoxLayout();
    QLabel* startLabel = new QLabel("Launch on startup");
    startLabel->setStyleSheet(labelStyle);

    QLabel* startDesc = new QLabel("Start app when system boots");
    startDesc->setStyleSheet(subLabelStyle);

    startupText->addWidget(startLabel);
    startupText->addWidget(startDesc);

    _startup = new QCheckBox();
    _startup->setStyleSheet(toggleStyle);

    startupLayout->addLayout(startupText);
    startupLayout->addStretch();
    startupLayout->addWidget(_startup);

    // Tray
    QHBoxLayout* trayLayout = new QHBoxLayout();

    QVBoxLayout* trayText = new QVBoxLayout();
    QLabel* trayLabel = new QLabel("Minimize to tray");
    trayLabel->setStyleSheet(labelStyle);

    QLabel* trayDesc = new QLabel("Keep app running in background");
    trayDesc->setStyleSheet(subLabelStyle);

    trayText->addWidget(trayLabel);
    trayText->addWidget(trayDesc);

    _tray = new QCheckBox();
    _tray->setStyleSheet(toggleStyle);

    trayLayout->addLayout(trayText);
    trayLayout->addStretch();
    trayLayout->addWidget(_tray);

    behLayout->addWidget(behTitle);
    behLayout->addLayout(startupLayout);
    behLayout->addLayout(trayLayout);

    main->addWidget(behavior);

    main->addStretch();
}