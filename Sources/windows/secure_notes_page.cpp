#include "windows/secure_notes_page.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QEvent>
#include <QMouseEvent>
#include <QTextEdit>

// ================= CONSTRUCTOR =================

secure_notes_page::secure_notes_page(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    loadFakeData();
}

// ================= UI =================

void secure_notes_page::setupUI()
{
    setStyleSheet("background-color: #020617;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    // ===== TOP BAR =====
    QHBoxLayout* topLayout = new QHBoxLayout();

    _search = new QLineEdit();
    _search->setPlaceholderText("Search notes...");
    _search->setStyleSheet(R"(
        QLineEdit {
            background-color: #0F172A;
            color: white;
            padding: 10px;
            border-radius: 10px;
        }
    )");

    _addBtn = new QPushButton("+ Add Note");
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

    // ===== SCROLL AREA =====
    _scrollArea = new QScrollArea();
    _scrollArea->setWidgetResizable(true);
    _scrollArea->setFrameShape(QFrame::NoFrame);
    _scrollArea->setStyleSheet("background: transparent;");

    _container = new QWidget();
    _grid = new QGridLayout(_container);
    _grid->setSpacing(20);
    _grid->setContentsMargins(0, 0, 0, 0);

    _scrollArea->setWidget(_container);

    mainLayout->addWidget(_scrollArea);
}

// ================= DATA =================

void secure_notes_page::loadFakeData()
{
    struct Note {
        QString title;
        QString preview;
        QString full;
        QString date;
    };

    QList<Note> notes = {
        {"AWS Keys", "Access Key: AKIA****", "Access Key: AKIA123\nSecret: VERY_SECRET_KEY\nRegion: us-east-1", "Edited 2 days ago"},
        {"Server Config", "SSH root password...", "Host: 192.168.1.1\nUser: root\nPassword: 123456", "Edited yesterday"},
        {"Crypto Wallet", "Seed phrase stored...", "word1 word2 word3 ... word12", "Edited 5 days ago"},
        {"Private Notes", "Some very secret text...", "Full private content goes here...", "Edited today"}
    };

    int row = 0, col = 0;
    int maxCols = 3;

    for (const auto& note : notes)
    {
        QWidget* card = createNoteCard(note.title, note.preview, note.full, note.date);
        _grid->addWidget(card, row, col);

        col++;
        if (col >= maxCols) {
            col = 0;
            row++;
        }
    }

    _grid->setRowStretch(row + 1, 1);
}

// ================= CARD =================

QWidget* secure_notes_page::createNoteCard(const QString& title,
                                           const QString& preview,
                                           const QString& fullText,
                                           const QString& date)
{
    QFrame* card = new QFrame();
    card->setCursor(Qt::PointingHandCursor);

    card->setStyleSheet(R"(
        QFrame {
            background-color: #0F172A;
            border-radius: 16px;
        }
        QFrame:hover {
            background-color: #1E293B;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(card);
    layout->setContentsMargins(15, 15, 15, 15);

    QLabel* titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("color: white; font-weight: bold; font-size: 15px;");

    QLabel* previewLabel = new QLabel(preview);
    previewLabel->setStyleSheet("color: #94A3B8;");
    previewLabel->setWordWrap(true);

    QLabel* dateLabel = new QLabel(date);
    dateLabel->setStyleSheet("color: #64748B; font-size: 11px;");

    layout->addWidget(titleLabel);
    layout->addWidget(previewLabel);
    layout->addStretch();
    layout->addWidget(dateLabel);

    // 🔥 store data inside widget
    card->setProperty("title", title);
    card->setProperty("content", fullText);

    // 🔥 install click handler
    card->installEventFilter(this);

    return card;
}

// ================= CLICK HANDLER =================

bool secure_notes_page::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QWidget* card = qobject_cast<QWidget*>(obj);
        if (card)
        {
            QString title = card->property("title").toString();
            QString content = card->property("content").toString();

            openNoteDialog(title, content);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

// ================= DIALOG =================

void secure_notes_page::openNoteDialog(const QString& title, const QString& content)
{
    QDialog* dlg = new QDialog(this);
    dlg->setModal(true);
    dlg->resize(700, 500);
    dlg->setStyleSheet(R"(
        QDialog {
            background-color: #020617;
            border-radius: 16px;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(dlg);
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel* titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("color: white; font-size: 20px; font-weight: bold;");

    QTextEdit* text = new QTextEdit();
    text->setText(content);
    text->setReadOnly(true);
    text->setStyleSheet(R"(
        QTextEdit {
            background-color: #0F172A;
            color: white;
            border-radius: 10px;
            padding: 10px;
        }
    )");

    QPushButton* closeBtn = new QPushButton("Close");
    closeBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #2563EB;
            color: white;
            padding: 10px;
            border-radius: 10px;
        }
    )");

    layout->addWidget(titleLabel);
    layout->addWidget(text);
    layout->addWidget(closeBtn);

    connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);

    dlg->exec();
}