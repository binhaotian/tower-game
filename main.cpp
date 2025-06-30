#include <QApplication>
#include <QMessageBox>
#include "GameView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameView* g = new GameView(nullptr);
    g->show();    

    return a.exec();
}
