#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollArea>
#include <QDialog>

class secure_notes_page : public QWidget
{
    Q_OBJECT

public:
    explicit secure_notes_page(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void setupUI();
    void loadFakeData();
    QWidget* createNoteCard(const QString& title,
                            const QString& preview,
                            const QString& fullText,
                            const QString& date);

    void openNoteDialog(const QString& title, const QString& content);

private:
    QLineEdit* _search;
    QPushButton* _addBtn;

    QScrollArea* _scrollArea;
    QWidget* _container;
    QGridLayout* _grid;
};