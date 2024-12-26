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
    int tileWidth = 50;  // Width of each tile
    int tileHeight = 50; // Height of each tile
    int numTilesX = 10;  // Number of tiles horizontally
    int numTilesY = 9;  // Number of tiles vertically

    int gridWidth = numTilesX * tileWidth;
    int gridHeight = numTilesY * tileHeight;

    GiuGameController controller;
    controller.setGameLoader(std::make_unique<WorldLoader>());
    controller.setInputManager(nullptr); // TODO
    controller.init(this);

    // create main view and bind to controller
    QGraphicsView *view = new QGraphicsView(controller.getScene(), this);

    // Set view properties
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(gridWidth+200, gridHeight);
    this->setCentralWidget(view);
}

MainWindow::~MainWindow() {}
