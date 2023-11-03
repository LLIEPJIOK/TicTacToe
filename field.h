#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QString>
#include <QPushButton>
#include <thread>
#include <chrono>

class Field : public QWidget
{
    Q_OBJECT
public:
    Field(int _size, int _good, bool _is_computer, QWidget *parent = nullptr);
private:
    QPushButton *clear_btn;
    QGridLayout *grid_lay;
    QLabel *label_X;
    QLabel *label_O;
    QLabel *label_score;
    QLabel *label_show_win;
    char **arr;
    int good;
    int size;
    int btn_size;
    float wins_X;
    float wins_O;
    bool is_computer;
    char check();
    bool is_draw();
    bool check_all();
    std::pair<int, int> move();
    void set(int x, int y);
private slots:
    void set_check();
    void clear_field();
};

#endif // FIELD_H
