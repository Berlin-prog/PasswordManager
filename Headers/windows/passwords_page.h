#ifndef PASSWORDS_PAGE_H
#define PASSWORDS_PAGE_H


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QWidget>
class passwords_page : public QWidget
{
    Q_OBJECT
public:
    explicit passwords_page(QWidget* parent = nullptr);
private:
    void loadFakeData();

private:
    QLineEdit* _search;
    QPushButton* _addBtn;
    QTableWidget* _table;
};

#endif // PASSWORDS_PAGE_H
