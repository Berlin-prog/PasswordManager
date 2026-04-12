#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include <QWidget>

class QCheckBox;
class QComboBox;
class QLabel;

class settings_page : public QWidget
{
    Q_OBJECT

public:
    explicit settings_page(QWidget* parent = nullptr);

private:
    void setupUI();
    QWidget* createSection(const QString& title);

private:
    // Security
    QComboBox* _autoLock;
    QCheckBox* _clearClipboard;

    // Appearance
    QComboBox* _theme;

    // Behavior
    QCheckBox* _startup;
    QCheckBox* _tray;
};

#endif // SETTINGS_PAGE_H