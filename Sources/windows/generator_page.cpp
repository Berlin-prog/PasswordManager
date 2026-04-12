#include "windows/generator_page.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QRandomGenerator>
#include <QClipboard>
#include <QApplication>
#include <QPropertyAnimation>

// ================= CONSTRUCTOR =================

generator_page::generator_page(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    generatePassword();
}

// ================= UI =================

void generator_page::setupUI()
{
    setStyleSheet("background-color: #020617;");

    QVBoxLayout* main = new QVBoxLayout(this);
    main->setContentsMargins(40, 40, 40, 40);
    main->setSpacing(25);

    // ===== TITLE =====
    QLabel* title = new QLabel("Password Generator");
    title->setStyleSheet("color: white; font-size: 24px; font-weight: bold;");
    main->addWidget(title);

    // ===== OUTPUT =====
    QHBoxLayout* outputLayout = new QHBoxLayout();

    _output = new QLineEdit();
    _output->setReadOnly(true);
    _output->setStyleSheet(R"(
        QLineEdit {
            background-color: #0F172A;
            color: white;
            padding: 12px;
            border-radius: 10px;
            font-size: 16px;
        }
    )");

    _copyBtn = new QPushButton("Copy");
    _copyBtn->setCursor(Qt::PointingHandCursor);
    _copyBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #2563EB;
            color: white;
            padding: 10px;
            border-radius: 10px;
        }
        QPushButton:hover {
            background-color: #1D4ED8;
        }
    )");

    outputLayout->addWidget(_output);
    outputLayout->addWidget(_copyBtn);

    main->addLayout(outputLayout);

    // ===== LENGTH =====
    _lengthLabel = new QLabel("Length: 12");
    _lengthLabel->setStyleSheet("color: #CBD5E1;");

    _lengthSlider = new QSlider(Qt::Horizontal);
    _lengthSlider->setRange(6, 32);
    _lengthSlider->setValue(12);
    _lengthSlider->setStyleSheet(R"(
        QSlider::groove:horizontal {
            height: 6px;
            background: #1E293B;
            border-radius: 3px;
        }
        QSlider::handle:horizontal {
            background: #2563EB;
            width: 16px;
            border-radius: 8px;
        }
    )");

    main->addWidget(_lengthLabel);
    main->addWidget(_lengthSlider);

    // ===== OPTIONS =====
    _uppercase = new QCheckBox("Uppercase (A-Z)");
    _lowercase = new QCheckBox("Lowercase (a-z)");
    _numbers   = new QCheckBox("Numbers (0-9)");
    _symbols   = new QCheckBox("Symbols (!@#)");

    _uppercase->setChecked(true);
    _lowercase->setChecked(true);
    _numbers->setChecked(true);

    QString checkboxStyle = R"(
        QCheckBox {
            color: white;
            font-size: 14px;
        }
    )";

    _uppercase->setStyleSheet(checkboxStyle);
    _lowercase->setStyleSheet(checkboxStyle);
    _numbers->setStyleSheet(checkboxStyle);
    _symbols->setStyleSheet(checkboxStyle);

    main->addWidget(_uppercase);
    main->addWidget(_lowercase);
    main->addWidget(_numbers);
    main->addWidget(_symbols);

    // ===== STRENGTH =====
    _strengthLabel = new QLabel("Strength: Medium");
    _strengthLabel->setStyleSheet("color: #FACC15; font-weight: bold;");
    main->addWidget(_strengthLabel);

    // ===== GENERATE BUTTON =====
    _generateBtn = new QPushButton("Generate Password");
    _generateBtn->setCursor(Qt::PointingHandCursor);

    _generateBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #10B981;
            color: white;
            padding: 14px;
            border-radius: 12px;
            font-size: 15px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #059669;
        }
    )");

    main->addWidget(_generateBtn);

    main->addStretch();

    // ===== CONNECTIONS =====

    connect(_generateBtn, &QPushButton::clicked, this, &generator_page::generatePassword);

    connect(_copyBtn, &QPushButton::clicked, [=]() {
        QApplication::clipboard()->setText(_output->text());
    });

    connect(_lengthSlider, &QSlider::valueChanged, [=](int value){
        _lengthLabel->setText("Length: " + QString::number(value));
    });
}

// ================= LOGIC =================

void generator_page::generatePassword()
{
    int length = _lengthSlider->value();
    QString password = buildPassword(length);

    _output->setText(password);
    updateStrengthIndicator(password);

    // 🔥 simple animation
    QPropertyAnimation* anim = new QPropertyAnimation(_output, "maximumWidth");
    anim->setDuration(150);
    anim->setStartValue(_output->width() - 10);
    anim->setEndValue(_output->width());
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

QString generator_page::buildPassword(int length)
{
    QString chars;

    if (_uppercase->isChecked()) chars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (_lowercase->isChecked()) chars += "abcdefghijklmnopqrstuvwxyz";
    if (_numbers->isChecked())   chars += "0123456789";
    if (_symbols->isChecked())   chars += "!@#$%^&*()";

    if (chars.isEmpty()) return "";

    QString result;

    for (int i = 0; i < length; ++i)
    {
        int index = QRandomGenerator::global()->bounded(chars.size());
        result += chars[index];
    }

    return result;
}

void generator_page::updateStrengthIndicator(const QString& password)
{
    int score = password.length();

    if (password.contains(QRegularExpression("[A-Z]"))) score++;
    if (password.contains(QRegularExpression("[0-9]"))) score++;
    if (password.contains(QRegularExpression("[!@#$%^&*]"))) score++;

    if (score < 10) {
        _strengthLabel->setText("Strength: Weak");
        _strengthLabel->setStyleSheet("color: #EF4444;");
    }
    else if (score < 15) {
        _strengthLabel->setText("Strength: Medium");
        _strengthLabel->setStyleSheet("color: #FACC15;");
    }
    else {
        _strengthLabel->setText("Strength: Strong");
        _strengthLabel->setStyleSheet("color: #10B981;");
    }
}