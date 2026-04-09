#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QVector>
#include "abstract_window.h"
#include "windows/dashboard_page.h"
#include "windows/passwords_page.h"
class main_window : public abstract_window
{
    Q_OBJECT
public:
    explicit main_window(QWidget* parent = nullptr);
    void setupUI() override;
    void setUserData(const QString& username);
private:
    dashboard_page* _dashboard;
    passwords_page* _passwords;
    QWidget* _notes;
    QWidget* _generator;
    QWidget* _settings;
};

#endif // MAIN_WINDOW_H
