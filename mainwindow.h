#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "compositeinputmanager.h"

class GiuGameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    GiuGameController *controller;
    CompositeInputManager *input;

public slots:
    void switchView();
  };

#endif // MAINWINDOW_H
