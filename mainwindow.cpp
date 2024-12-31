#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include "worldloader.h"
#include "GiuGameController.h"
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

    // add side menu
    QButtonGroup *buttons = new QButtonGroup(central);
    buttons->addButton(new QPushButton("Switch View", central));

    this->setCentralWidget(central);

}

MainWindow::~MainWindow() {}
