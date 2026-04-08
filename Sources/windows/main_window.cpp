#include "windows/main_window.h"

main_window::main_window(QWidget* parent) : abstract_window(parent) {};

void main_window::setupUI()
{
    this->setMinimumSize(1200, 800);
    abstract_window::setupUI();
}