#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GiuGameController;
class InputManager2d;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    GiuGameController *controller;
    InputManager2d *input;
    Ui::MainWindow *ui;
  };

#endif // MAINWINDOW_H
