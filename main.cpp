#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include "world.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    World wrld;
    wrld.createWorld(":/img/test.png",1, 1);
    int c = wrld.getCols();
    int r = wrld.getRows();
    std::vector<std::unique_ptr<Tile>> tiles = wrld.getTiles();
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            std::cout << tiles.at(i*c + j)->getValue() << ", ";
        }
        std::cout << std::endl;
    }

    return a.exec();
}
