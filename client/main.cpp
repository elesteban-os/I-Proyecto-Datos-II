#include "mainwindow.h"

#include <QApplication>

/**
 * @brief Inicia la intefaz gráfica y todo lo necesario para la lógica del juego.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
