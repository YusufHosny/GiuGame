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
#include "inputmanagertext.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // create central widget and layout
    QWidget *central = new QWidget;
    QBoxLayout *bl = new QBoxLayout(QBoxLayout::TopToBottom, central);

    // add menu
    QPushButton* svButton = new QPushButton("Switch View", central);
    bl->addWidget(svButton);
    connect(svButton, SIGNAL(clicked(bool)), this, SLOT(switchView()));

    // create input manager
    this->input = new CompositeInputManager(this);
    InputManager2d* im2d = new InputManager2d(this);
    InputManagerText* imt = new InputManagerText(central);
    this->input->addInputManager(im2d);
    this->input->addInputManager(imt);
    bl->addWidget(imt->getTextBar());

    // create main controller and bind to input manager
    this->controller = new GiuGameController(this->input);
    this->controller
        ->setGameLoader(std::make_unique<WorldLoader>())
        .setInputManager(this->input);
    this->controller->init(im2d);
    this->controller->start();

    bl->addWidget(controller->getView());

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
