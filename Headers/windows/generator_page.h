#ifndef GENERATOR_PAGE_H
#define GENERATOR_PAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QRegularExpression>

class generator_page : public QWidget
{
    Q_OBJECT

public:
    explicit generator_page(QWidget* parent = nullptr);

private:
    void setupUI();
    void generatePassword();
    QString buildPassword(int length);
    void updateStrengthIndicator(const QString& password);

private:
    QLineEdit* _output;
    QPushButton* _copyBtn;
    QPushButton* _generateBtn;

    QSlider* _lengthSlider;
    QLabel* _lengthLabel;

    QCheckBox* _uppercase;
    QCheckBox* _lowercase;
    QCheckBox* _numbers;
    QCheckBox* _symbols;

    QLabel* _strengthLabel;
};
#endif // GENERATOR_PAGE_H
