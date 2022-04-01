#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , server (new Server)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startServerBtn_clicked()
{
    ui->startServerBtn->setEnabled(false);
    ui->logText->appendPlainText("Iniciando server");
    server->startServer();
    ui->logText->appendPlainText("Server iniciado");
}


void MainWindow::on_sendImgBtn_clicked()
{
    QImage img2("descarga.jpg");

    // Extraer datos de la imagen.
    int size = img2.sizeInBytes();
    char data[size];
    memcpy(data, img2.bits(), size);

    for (int i = 0; i < 20; i++) {
        printf("%x", data[i]);
    }


    // Enviar imagen
    server->sendMessage("newimage\0", 0);
    server->sendMessage(data, 0, size);

    // Para ver la imagen
    QImage imgdata((uchar*)data, 225, 225, QImage::Format_ARGB32);
    QPixmap p(QPixmap::fromImage(imgdata));
    ui->label1->setPixmap(p);
}

