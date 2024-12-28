#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include "worldloader.h"
#include "GiuGameController.h"
#include "inputmanager2d.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // create input manager
    this->input = new InputManager2d(this);

    // create main controller and bind to input manager
    this->controller = new GiuGameController(this->input);
    this->controller
        ->setGameLoader(std::make_unique<WorldLoader>())
        .setInputManager(this->input);
    this->controller->init(this->input);

    this->controller->start();

    this->setCentralWidget(controller->getView());
}

MainWindow::~MainWindow() {}
