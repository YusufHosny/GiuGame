#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include "worldloader.h"
#include "levelobject.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
  {
  ui->setupUi(this);
  QGraphicsScene * scene = new QGraphicsScene(this);

  WorldLoader wl;
  std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(wl.load(":img/test.png"));

  ui->graphicsView->setScene(scene);
  auto rect = scene->addRect(10, 50, 50, 120);
  rect->setZValue(1.1);
  rect->setFlag(QGraphicsItem::ItemIsMovable, true);
  }

MainWindow::~MainWindow()
  {
  delete ui;
  //I don't need to delete scene or rect since everything what derives from QObject has also a parent
  //when the toplevel QObject (ui in this case) is deleted, all its children will also be deleted
  //So there is no urgent need to work with smart pointers for all QObject derived stuff you use
  }
