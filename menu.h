#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget *parent = nullptr);
private:
    QLabel *label_size;
    QLineEdit *edit_size;
    QLabel *label_wrong_size;
    QLabel *label_good;
    QLineEdit *edit_good;
    QLabel *label_wrong_good;
    QCheckBox *is_computer;
    QGridLayout *gridlay;
    QVBoxLayout *vblay;
    QVBoxLayout *size_vblay;
    QVBoxLayout *good_vblay;
    QPushButton *btn_start;
private slots:
    void start_game_slot();
signals:
    void start_game_signal(int size, int good, bool is_computer);
};

#endif // MENU_H
