#ifndef DASHBOARD_PAGE_H
#define DASHBOARD_PAGE_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class dashboard_page : public QWidget
{
    Q_OBJECT
public:
    explicit dashboard_page(QWidget* parent = nullptr);
    void setUsername(const QString& username);
private:
    QWidget* createCard(const QString& title, const QString& value);
    QLabel* _welcomeLabel;
};

#endif // DASHBOARD_PAGE_H

