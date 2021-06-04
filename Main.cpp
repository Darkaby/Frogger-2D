#include <QtWidgets>
#include <QDebug>
#include <QMessageBox>
#include "truck.h"
#include "game.h"

#define RECT_WIDTH 40
#define RECT_HEIGHT 10
#define NUM_TRUCK 5

int main(int argc, char *argv[])
{

    //int pos = 50;
    //int space_trucks = 100;

    QApplication app(argc, argv);      // Loads the QPA plugin

    Game game(10, 100);

    game.show();
    return app.exec();                 // Starts the event loop
}
