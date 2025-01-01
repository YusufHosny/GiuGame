#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include "worldloader.h"
#include "giugamecontroller.h"
#include "inputmanager2d.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // create central widget and layout
    QWidget *central = new QWidget;
    QBoxLayout *bl = new QBoxLayout(QBoxLayout::LeftToRight, central);

    // create input manager
    this->input = new InputManager2d(this);

    // create main controller and bind to input manager
    this->controller = new GiuGameController(this->input);
    this->controller
        ->setGameLoader(std::make_unique<WorldLoader>())
        .setInputManager(this->input);
    this->controller->init(this->input);
    this->controller->start();

    bl->addWidget(controller->getView());

    // add menu
    QButtonGroup *buttons = new QButtonGroup(central);
    buttons->addButton(new QPushButton("Switch View", central));

    connect(buttons, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(switchView()));

    this->setCentralWidget(central);

}

void MainWindow::switchView() {
    QGraphicsView *prev = this->controller->getView();
    QTransform t = prev->transform();
    QRectF r = prev->mapToScene(prev->viewport()->geometry()).boundingRect();
    this->centralWidget()->layout()->removeWidget(prev);
    this->controller->getView()->hide();

    this->controller->changeView();
    QGraphicsView *next = this->controller->getView();
    next->setTransform(t);
    next->ensureVisible(r);
    this->centralWidget()->layout()->addWidget(next);
    this->controller->getView()->show();
}



MainWindow::~MainWindow() {}
