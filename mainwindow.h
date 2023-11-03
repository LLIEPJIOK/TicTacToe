#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "field.h"
#include "menu.h"

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Field *field;
    Menu *menu;
    QMenu *qmenu;
    QAction *go_to_menu;
private slots:
    void start_game_slot(int size, int good, bool is_computer);
    void open_menu();
};
#endif // MAINWINDOW_H
