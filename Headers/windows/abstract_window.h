#ifndef ABSTRACT_WINDOW_H
#define ABSTRACT_WINDOW_H

#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>

class abstract_window : public QWidget
{
    Q_OBJECT
public:
    explicit abstract_window(QWidget* parent = nullptr);
    virtual ~abstract_window() = default;

    virtual void setupUI() = 0;
    void showMessage(const QString& titla, const QString& message);
    void showError(const QString& message);
    void setActiveButton(QPushButton* active);
    void setUsername(const QString& username);
signals:
    void logoutRequested();
protected:
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
    QStackedWidget* _content;
};

#endif // ABSTRACT_WINDOW_H
