#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientsock.h"
#include <thread>
#include <string.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client(new clientSock)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::threadData() {
    while (1) {
        std::cout << (client->getData());
    }
}

void MainWindow::on_connectBtn_clicked()
{
    client->startClient();
    //std::thread();
}




void MainWindow::on_seeImageBtn_clicked()
{
    char *data = client->getData();
    printf("%s", data);
    QImage imgdata((uchar*)data, 225, 225, QImage::Format_ARGB32);
    QPixmap p(QPixmap::fromImage(imgdata));
    ui->label->setPixmap(p);
}

