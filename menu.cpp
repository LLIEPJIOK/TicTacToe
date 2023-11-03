#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    Q_UNUSED(parent);

    label_size = new QLabel();
    label_size->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    label_size->setText("Введите длину стороны поля");
    label_size->setFont(QFont("Arial", 10, QFont::Normal, 1));
    label_size->setMinimumSize(250, 20);

    edit_size = new QLineEdit();
    edit_size->setMinimumSize(250, 26);

    label_wrong_size = new QLabel();
    label_wrong_size->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    label_wrong_size->setMinimumSize(250, 15);
    label_wrong_size->setStyleSheet("color : rgb(255, 0, 0)");
    label_wrong_size->setFont(QFont("Arial", 8, QFont::Normal, 1));


    size_vblay = new QVBoxLayout();
    size_vblay->setAlignment(Qt::AlignCenter);
    size_vblay->addWidget(label_size);
    size_vblay->addWidget(edit_size);
    size_vblay->addWidget(label_wrong_size);
    size_vblay->setSpacing(0);


    label_good = new QLabel();
    label_good->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    label_good->setText("Введите количество символов для победы");
    label_good->setFont(QFont("Arial", 10, QFont::Normal, 1));
    label_good->setMinimumSize(250, 20);

    edit_good = new QLineEdit();
    edit_good->setMinimumSize(250, 26);

    label_wrong_good = new QLabel();
    label_wrong_good->setMinimumSize(250, 15);
    label_wrong_good->setStyleSheet("color : rgb(255, 0, 0)");
    label_wrong_good->setFont(QFont("Arial", 8, QFont::Normal, 1));
    label_wrong_good->setStyleSheet("color : rgb(255, 0, 0)");
    label_wrong_good->setFont(QFont("Arial", 8, QFont::Normal, 1));

    good_vblay = new QVBoxLayout();
    good_vblay->setAlignment(Qt::AlignCenter);
    good_vblay->addWidget(label_good);
    good_vblay->addWidget(edit_good);
    good_vblay->addWidget(label_wrong_good);
    good_vblay->setSpacing(0);

    is_computer = new QCheckBox();
    is_computer->setMinimumSize(250, 20);
    is_computer->setFont(QFont("Arial", 10));
    is_computer->setText("Игра с компьютером");

    btn_start = new QPushButton();
    btn_start->setFont(QFont("Arial", 10));
    btn_start->setText("Начать игру");
    btn_start->setMinimumSize(250, 30);

    gridlay = new QGridLayout();
    gridlay->addLayout(size_vblay, 0, 0);
    gridlay->addLayout(good_vblay, 1, 0);
    gridlay->addWidget(is_computer, 2, 0);
    gridlay->addWidget(btn_start, 3, 0);
    gridlay->setSpacing(10);

    vblay = new QVBoxLayout();
    vblay->setAlignment(Qt::AlignCenter);
    vblay->addLayout(gridlay);

    setLayout(vblay);
    setMinimumSize(300, 300);
    connect(btn_start, SIGNAL(clicked()), this, SLOT(start_game_slot()));
}

void Menu::start_game_slot()
{
    bool check_size;
    int size = edit_size->text().toInt(&check_size);
    if (!check_size && edit_size->text().isEmpty())
        label_wrong_size->setText("Пустое поле");
    else if (!check_size)
        label_wrong_size->setText("Некорректные данные");
    else if (size > 40)
        label_wrong_size->setText("Невозможно сгенерировать. Введите меньше 40");
    else if (size < 3)
        label_wrong_size->setText("Размер слишком маленький");
    else
        label_wrong_size->setText("");

    bool check_good;
    int good = edit_good->text().toInt(&check_good);
    if (!check_good && edit_good->text().isEmpty())
        label_wrong_good->setText("Пустое поле");
    else if(!check_good)
        label_wrong_good->setText("Некорректные данные");
    else if (good > size)
        label_wrong_good->setText("Количество символов не должно превышать размер");
    else if(good < 3)
        label_wrong_good->setText("Количество слишком маленькое");
    else
        label_wrong_good->setText("");
    if (label_wrong_size->text().isEmpty() && label_wrong_good->text().isEmpty())
    {
        emit start_game_signal(size, good, is_computer->isChecked());
        edit_size->setText("");
        edit_good->setText("");
        is_computer->setChecked(0);
    }
}
