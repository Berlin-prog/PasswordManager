#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QVector>

class main_window : public QWidget
{
    Q_OBJECT
public:
    explicit main_window(QWidget* parent = nullptr);
    void setUsername(const QString& username);
private:
    void setupUI();
    void setActiveButton(QPushButton* active);
signals:
    void logoutRequested();
private:
    QHBoxLayout* _mainLayout;
    QWidget* _sidebar;
    QVBoxLayout* _sidebarLayout;
    QPushButton* _dashboardBtn;
    QPushButton* _passwordsBtn;
    QPushButton* _notesBtn;
    QPushButton* _generatorBtn;
    QPushButton* _settingsBtn;
    QPushButton* _logoutBtn;
    QString _btnStyle;
    QString _activeStyle;
    QLabel* _username;
};

#endif // MAIN_WINDOW_H
