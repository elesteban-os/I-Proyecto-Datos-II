#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "memory.h"
#include "card.h"
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , server (new Server)
{
    ui->setupUi(this);
    changeMemoryUsageHelper();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::changeMemoryUsageHelper() {
    std::thread tMemory(&MainWindow::changeMemoryUsage, this);
    tMemory.detach();
}

void MainWindow::changeMemoryUsage() {
    int num;
    QString numS;
    while (1) {
        num = memoryManager.getCurrentMemoryUsage();
        numS = QString::number(num);
        numS.append(" Bytes");
        ui->variableMemoryUsage->setText(numS);
        sleep_for(std::chrono::milliseconds(1000));
    }
}

void MainWindow::inMemoryCardsInfo() {
    while (1) {
        QTableWidgetItem *item = new QTableWidgetItem(memoryManager.getInMemoryCardsInfo());
        QTableWidgetItem *item1 = new QTableWidgetItem(memoryManager.getInDiscCardsInfo());
        memoryManager.inMemoryCards.deleteLastData();
        memoryManager.createInMemoryCardsInfo();
        memoryManager.createInDiscCardsInfo();
        ui->tableWidget->setItem(0, 0, item);
        ui->tableWidget->setItem(0, 1, item1);
        this->tablei++;
        sleep_for(std::chrono::milliseconds(1000));
    }
}

void MainWindow::on_startServerBtn_clicked()
{
    ui->startServerBtn->setEnabled(false);
    ui->logText->appendPlainText("Iniciando server");
    server->startServer();
    ui->logText->appendPlainText("Server iniciado");

    // Para tratar la tabla.
    std::thread tMemory(&MainWindow::inMemoryCardsInfo, this);
    tMemory.detach();
}


void MainWindow::on_sendImgBtn_clicked()
{
    // Const char para el array
    const char *imageName = "images/1.jpg";

    // Char para hacer la tarjeta
    char namee[10];

    // Copia de memoria a la variable para la tarjeta
    memcpy(namee, imageName, strlen(imageName));

    // Se puede crear imagenes con const char
    QImage img2(imageName);

    // Extraer datos de la imagen.
    int size = img2.sizeInBytes();
    char data[size];
    memcpy(data, img2.bits(), size);

    // Creacion de tarjeta
    card *card1 = new card(data, size, 0);


    for (int i = 0; i < 20; i++) {
        printf("%x", data[i]);
    }


    // Enviar imagen
    server->sendMessage("newimage\0", 0);
    server->sendMessage(data, 0, size);

    // Para ver la imagen
    QImage imgdata((uchar*)card1->getImage(), 100, 100, QImage::Format_ARGB32);
    QPixmap p(QPixmap::fromImage(imgdata));
    ui->label1->setPixmap(p);
}

