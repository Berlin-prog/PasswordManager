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
class main_window : public abstract_window
{
    Q_OBJECT
public:
    explicit main_window(QWidget* parent = nullptr);
    void setupUI() override;
};

#endif // MAIN_WINDOW_H
