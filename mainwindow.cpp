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

    this->controller = new GiuGameController;
    this->controller->setParent(this);
    this->controller
        ->setGameLoader(std::make_unique<WorldLoader>())
        .setInputManager(nullptr); // TODO
    this->controller->init(this);

    this->controller->start();

    this->setCentralWidget(controller->getView());
}

MainWindow::~MainWindow() {}
