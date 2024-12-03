#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include "worldloader.h"
#include "levelobject.h"
#include "Views/2d/GameView2d.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    int tileWidth = 50;  // Width of each tile
    int tileHeight = 50; // Height of each tile
    int numTilesX = 10;  // Number of tiles horizontally
    int numTilesY = 9;  // Number of tiles vertically

    int gridWidth = numTilesX * tileWidth;
    int gridHeight = numTilesY * tileHeight;



    WorldLoader wl;
    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(wl.load(":img/test.png"));

    GameView2d *gameView = new GameView2d(this,lo);


    QGraphicsView *view = new QGraphicsView(gameView, this);

    // Set view properties
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(gridWidth+1, gridHeight+1); // Set your desired view size

    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    // Nothing to manually delete since parent-child takes care of it
}
