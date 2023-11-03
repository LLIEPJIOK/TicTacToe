#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>

class Button : public QPushButton
{
public:
    Button(const int& _x, const int& _y, QWidget *parent = nullptr);
    int get_x();
    int get_y();
private:
    int x;
    int y;
};

#endif // BUTTON_H
