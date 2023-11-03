#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    menu = new Menu();
    setCentralWidget(menu);
    resize(centralWidget()->minimumSize());
    move(300, 10);
    go_to_menu = new QAction("Перейти в меню");
    qmenu = new QMenu();
    qmenu = menuBar()->addMenu("&Меню");
    qmenu->addAction(go_to_menu);
    connect(menu, &Menu::start_game_signal, this, &MainWindow::start_game_slot);
    connect(go_to_menu, &QAction::triggered, this, &MainWindow::open_menu);
    //setMaximumSize(500, 300); - фиксированный размер
    //setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint); - скрытие кнопки на весь экран
    //setWindowFlags(windowFlags() ^ Qt::WindowMinMaxButtonsHint); - скрытие кнопки на весь экран и свернуть
}

MainWindow::~MainWindow()
{

}

void MainWindow::start_game_slot(int size, int good, bool is_computer)
{
    field = new Field(size, good, is_computer);
    menu->setParent(0);
    setCentralWidget(field);
    resize(centralWidget()->minimumSize());
}

void MainWindow::open_menu()
{
    setCentralWidget(menu);
}

