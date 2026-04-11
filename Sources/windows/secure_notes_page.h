#ifndef SECURE_NOTES_PAGE_H
#define SECURE_NOTES_PAGE_H
#include <QWidget>
class secure_notes_page : public QWidget
{
    Q_OBJECT
public:
    explicit secure_notes_page(QWidget* parent = nullptr);

private:
    void setupUI();
    void loadFakeData();
    QWidget* createNoteCard(const QString& title, const QString& preview, const QString& date);
};

#endif // SECURE_NOTES_PAGE_H
