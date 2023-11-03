#include "button.h"

Button::Button( const int& _x, const int& _y, QWidget *parent) : QPushButton()
{
    Q_UNUSED(parent);
    x = _x;
    y = _y;
}

int Button::get_x()
{
    return x;
}

int Button::get_y()
{
    return y;
}
