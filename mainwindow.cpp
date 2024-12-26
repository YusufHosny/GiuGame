#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include "worldloader.h"
#include "GiuGameController.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    GiuGameController controller;
    controller.setGameLoader(std::make_unique<WorldLoader>());
    controller.setInputManager(nullptr); // TODO
    controller.init(this);


    this->setCentralWidget(controller.getView());
}

MainWindow::~MainWindow() {}
