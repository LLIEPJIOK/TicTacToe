#include "field.h"
#include "button.h"

#define btn(i, j) ((Button*)grid_lay->itemAtPosition((i + 2), (j))->widget())

Field::Field(int _size, int _good, bool _is_computer, QWidget *parent) : QWidget(parent)
{
    Q_UNUSED(parent);
    good = _good;
    size = _size;
    is_computer = _is_computer;
    wins_X = 0;
    wins_O = 0;
    arr = new char*[size];
    for (int i = 0; i < size; ++i)
    {
        arr[i] = new char[size];
        for (int j = 0; j < size; ++j)
            arr[i][j] = 0;
    }

    grid_lay = new QGridLayout(this);
    grid_lay->setSpacing(0);

    label_X = new QLabel();
    label_X->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    label_X->setContentsMargins(5, 0, 0, 0);
    label_X->setStyleSheet("color : rgb(255, 0, 0)");
    if (!is_computer)
        label_X->setText("<h3>Игрок 1 (X)</h3>");
    else
        label_X->setText("<h2>Игрок (X)</h2>");

    label_O = new QLabel();
    label_O->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    label_O->setStyleSheet("color : rgb(0, 0, 255)");
    label_O->setContentsMargins(0, 0, 5, 0);
    if (!is_computer)
        label_O->setText("<h3>Игрок 2 (O)</h3>");
    else
        label_O->setText("<h2>Бот (O)</h2>");
    label_O->setVisible(0);

    if (size < 6)
    {
        grid_lay->addWidget(label_X, 1, 0);
        grid_lay->addWidget(label_O, 1, size - 1);
    }
    else if (size < 12)
    {
        grid_lay->addWidget(label_X, 1, 0, 1, 2);
        grid_lay->addWidget(label_O, 1, size - 2, 1, 2);
    }
    else
    {
        grid_lay->addWidget(label_X, 1, 0, 1, 7);
        grid_lay->addWidget(label_O, 1, size - 7, 1, 7);
    }

    btn_size = 450 / size;
    if (btn_size > 100)
        btn_size = 100;

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
        {
            Button *btn = new Button(i, j);
            connect(btn, &Button::clicked, this, &Field::set_check);
            btn->setMinimumSize(btn_size, btn_size);
            btn->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
            btn->setFont(QFont("Arial", (btn_size - 2) / 2));
            grid_lay->addWidget(btn, i + 2, j);
        }

    label_score = new QLabel();
    label_score->setMinimumHeight(35);
    label_score->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    label_score->setFont(QFont("Arial", 12));
    label_score->setText("\n<i>Счёт:</i><B> <FONT COLOR=RED>" + QString::number(wins_X) +
                       "</FONT> : <FONT COLOR=BLUE>" + QString::number(wins_O) + "</FONT></B>");
    grid_lay->addWidget(label_score, 1, 1, 1, size - 2);

    label_show_win = new QLabel();
    label_show_win->setAlignment(Qt::AlignCenter);
    label_show_win->setFont(QFont("Arial", 14, QFont::Bold));
    label_show_win->setMinimumHeight(25);
    label_show_win->setText("<I>Составьте ряд из " + QString::number(good) + " крестиков</I>");
    grid_lay->addWidget(label_show_win, 0, 0, 1, size);

    clear_btn = new QPushButton();
    clear_btn->setText("Очистить поле");
    clear_btn->setFont(QFont("Arial", 14));
    clear_btn->setEnabled(0);
    clear_btn->setMinimumHeight(30);
    grid_lay->addWidget(clear_btn, size + 2, 0, 1, size);

    setLayout(grid_lay);
    setMinimumSize(size * btn_size + 100, size * btn_size + 175);
    connect(clear_btn, &QPushButton::clicked, this, &Field::clear_field);
}

char Field::check()
{

    //rows
    for (int i = 0; i < size; ++i)
        for (int j = 0; j <= size - good; ++j)
        {
            char cur = arr[i][j];
            if (cur)
            {
                int k = 1;
                for (; k < good; ++k)
                    if (arr[i][j + k] != cur)
                        break;
                if (k == good)
                    return cur;
            }
        }
    //cols
    for (int i = 0; i <= size - good; ++i)
        for (int j = 0; j < size; ++j)
        {
            char cur = arr[i][j];
            if (cur)
            {
                int k = 1;
                for (; k < good; ++k)
                    if (arr[i + k][j] != cur)
                        break;
                if (k == good)
                    return cur;
            }
        }
    // (/)
    for (int i = good-1; i < size; ++i)
        for (int j = 0; j <= size - good; ++j)
        {
            char cur = arr[i][j];
            if (cur)
            {
                int k = 1;
                for (; k < good; ++k)
                    if (arr[i - k][j + k] != cur)
                        break;
                if (k == good)
                    return cur;
            }
        }
    // (\)
    for (int i = 0; i <= size - good; ++i)
        for (int j = 0; j <= size - good; ++j)
        {
            char cur = arr[i][j];
            if (cur != 0)
            {
                int k = 1;
                for (; k < good; ++k)
                    if (arr[i + k][j + k] != cur)
                        break;
                if (k == good)
                    return cur;
            }
        }
    return 0;
}

bool Field::is_draw()
{

    for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (!arr[i][j])
                    return 0;
    return 1;
}

bool Field::check_all()
{
    char ch = check();
    if (ch)
    {
        clear_btn->setEnabled(1);
        if (ch == 'X')
        {
            ++wins_X;
            label_show_win->setText("<FONT COLOR=RED>Крестики выиграли<FONT COLOR=RED>");
            label_score->setText("<i>Счёт:</i><B> <FONT COLOR=RED>" + QString::number(wins_X) +
                               "</FONT> : <FONT COLOR=BLUE>" + QString::number(wins_O) + "</FONT></B>");
            return 1;
        }
        ++wins_O;
        label_show_win->setText("<FONT COLOR=BLUE>Нолики выиграли<FONT COLOR=BLUE>");
        label_score->setText("<i>Счёт:</i><B> <FONT COLOR=RED>" + QString::number(wins_X) +
                           "</FONT> : <FONT COLOR=BLUE>" + QString::number(wins_O) + "</FONT></B>");
        return 1;
    }
    if (is_draw())
    {
        clear_btn->setEnabled(1);
        wins_X += 0.5;
        wins_O += 0.5;
        label_show_win->setText("Ничья");
        label_score->setText("<i>Счёт:</i><B> <FONT COLOR=RED>" + QString::number(wins_X) +
                           "</FONT> : <FONT COLOR=BLUE>" + QString::number(wins_O) + "</FONT></B>");
        return 1;
    }
    return 0;
}

void Field::set_check()
{
    if (clear_btn->isEnabled())
        return;
    Button *btn = (Button*)sender();
    if (!btn->text().isEmpty())
        return;
    if (label_X->isVisible())
    {
        btn->setStyleSheet("color : rgb(255, 0, 0)");
        btn->setText("X");
    }
    else
    {
        btn->setStyleSheet("color : rgb(0, 0, 255)");
        btn->setText("O");
    }
    set(btn->get_x(), btn->get_y());
    if (check_all())
        return;
    label_X->setVisible(!label_X->isVisible());
    label_O->setVisible(!label_O->isVisible());
    if (is_computer)
    {
        repaint();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        auto tmp = move();
        btn(tmp.first, tmp.second)->setText("O");
        btn(tmp.first, tmp.second)->setStyleSheet("color : rgb(0, 0, 255)");
        set(tmp.first, tmp.second);
        if (check_all())
            return;
        label_X->setVisible(!label_X->isVisible());
        label_O->setVisible(!label_O->isVisible());
    }
}

void Field::clear_field()
{
    for (int i = 0; i < size; ++i)
    {
        arr[i] = new char[size];
        for (int j = 0; j < size; ++j)
            arr[i][j] = 0;
    }
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            btn(i, j)->setText("");
    clear_btn->setEnabled(0);
    label_X->setVisible(!label_X->isVisible());
    label_O->setVisible(!label_O->isVisible());
    label_show_win->setText("Составьте ряд из " + QString::number(good) + " крестиков");
    if (is_computer && label_O->isVisible())
    {
        repaint();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        auto tmp = move();
        btn(tmp.first, tmp.second)->setText("O");
        btn(tmp.first, tmp.second)->setStyleSheet("color : rgb(0, 0, 255)");
        set(tmp.first, tmp.second);
        label_X->setVisible(!label_X->isVisible());
        label_O->setVisible(!label_O->isVisible());
    }
}

std::pair<int, int> Field::move()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (!arr[i][j])
            {
                arr[i][j] = 'O';
                char ch = check();
                arr[i][j] = 0;
                if (ch == 'O')
                    return {i, j};
            }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (!arr[i][j])
            {
                arr[i][j] = 'X';
                char ch = check();
                arr[i][j] = 0;
                if (ch == 'X')
                    return {i, j};
            }
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (arr[i][j] == 'O')
            {
                if (i + 1 < size && j + 1 < size && !arr[i + 1][j + 1])
                    return {i + 1, j + 1};
                if (i + 1 < size && j - 1 >= 0 && !arr[i + 1][j - 1])
                    return {i + 1, j - 1};
                if (i - 1 >= 0 && j + 1 < size && !arr[i - 1][j + 1])
                    return {i - 1, j + 1};
                if (i - 1 >= 0 && j - 1 >= 0 &&!arr[i - 1][j - 1])
                    return {i - 1, j - 1};
                if (i + 1 < size && !arr[i + 1][j])
                    return {i + 1, j};
                if (i - 1 >= 0 && !arr[i - 1][j])
                    return {i - 1, j};
                if (j + 1 < size && !arr[i][j + 1])
                    return {i, j + 1};
                if (j - 1 >= 0 && !arr[i][j - 1])
                    return {i, j - 1};
            }
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (arr[i][j] == 'X')
            {
                if (i + 1 < size && j + 1 < size && !arr[i + 1][j + 1])
                    return {i + 1, j + 1};
                if (i + 1 < size && j - 1 >= 0 && !arr[i + 1][j - 1])
                    return {i + 1, j - 1};
                if (i - 1 >= 0 && j + 1 < size && !arr[i - 1][j + 1])
                    return {i - 1, j + 1};
                if (i - 1 >= 0 && j - 1 >= 0 &&!arr[i - 1][j - 1])
                    return {i - 1, j - 1};
                if (i + 1 < size && !arr[i + 1][j])
                    return {i + 1, j};
                if (i - 1 >= 0 && !arr[i - 1][j])
                    return {i - 1, j};
                if (j + 1 < size && !arr[i][j + 1])
                    return {i, j + 1};
                if (j - 1 >= 0 && !arr[i][j - 1])
                    return {i, j - 1};
            }
    return {(size - 1) / 2, (size - 1) / 2};
}

void Field::set(int x, int y)
{
    arr[x][y] = label_X->isVisible() ? 'X' : 'O';
}
