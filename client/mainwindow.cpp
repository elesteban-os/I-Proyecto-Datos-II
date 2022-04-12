#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientsock.h"
#include <thread>
#include <string.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::time() {
    while(1) {
        sleep_for(std::chrono::milliseconds(1000));
        if (ui->timeMin01->value() == 9 && ui->timeSec10->value() == 5 && ui->timeSec01->value() == 9) {
            ui->timeMin10->display(ui->timeMin10->value() + 1);
            ui->timeMin01->display(0);
            ui->timeSec10->display(0);
            ui->timeSec01->display(0);
        } else if (ui->timeSec10->value() == 5 && ui->timeSec01->value() == 9) {
            ui->timeMin01->display(ui->timeMin01->value() + 1);
            ui->timeSec10->display(0);
            ui->timeSec01->display(0);
        } else if (ui->timeSec01->value() == 9) {
            ui->timeSec10->display(ui->timeSec10->value() + 1);
            ui->timeSec01->display(0);
        } else {
            ui->timeSec01->display(ui->timeSec01->value() + 1);
        }
    }
}

void MainWindow::threadData() {
    while (1) {
        std::cout << (client->getData());
    }
}

void MainWindow::on_connectBtn_clicked()
{
    client = new clientSock;
    client->startClient();
    //std::thread();
}

void MainWindow::changeImageButton(char *image, QPushButton* button) {
    QImage imgdata((uchar*)image, 100, 100, QImage::Format_ARGB32);
    QPixmap p(QPixmap::fromImage(imgdata));
    button->setIcon(p);
    button->setIconSize(QSize(100, 100));
}

void MainWindow::changeEnabledButton(bool enabled) {
    QPushButton *buttons[30] = {ui->card00, ui->card01, ui->card02, ui->card03, ui->card04, ui->card05,
                                ui->card10, ui->card11, ui->card12, ui->card13, ui->card14, ui->card15,
                                ui->card20, ui->card21, ui->card22, ui->card23, ui->card24, ui->card25,
                                ui->card30, ui->card31, ui->card32, ui->card33, ui->card34, ui->card35,
                                ui->card40, ui->card41, ui->card42, ui->card43, ui->card44, ui->card45};
    for (QPushButton *button : buttons) {
        button->setEnabled(enabled);
    }
}

void MainWindow::changeAllImageButton(char *image) {
    QPushButton *buttons[30] = {ui->card00, ui->card01, ui->card02, ui->card03, ui->card04, ui->card05,
                                ui->card10, ui->card11, ui->card12, ui->card13, ui->card14, ui->card15,
                                ui->card20, ui->card21, ui->card22, ui->card23, ui->card24, ui->card25,
                                ui->card30, ui->card31, ui->card32, ui->card33, ui->card34, ui->card35,
                                ui->card40, ui->card41, ui->card42, ui->card43, ui->card44, ui->card45};
    for (QPushButton *button : buttons) {
        changeImageButton(image, button);
    }
}

void MainWindow::on_seeImageBtn_clicked()
{
    char *data = client->getData();
    printf("%s", data);
    QImage imgdata((uchar*)data, 100, 100, QImage::Format_ARGB32);
    QPixmap p(QPixmap::fromImage(imgdata));
    //ui->label->setPixmap(p);
    ui->pushButton->setIcon(p);
    ui->pushButton->setIconSize(QSize(100, 100));




}

void MainWindow::isPlayable() {
    while (!client->getPlayable()) {
        sleep_for(std::chrono::milliseconds(1000));
    }
    game->setOpponentName(client->getEnemyName());
    changeAllImageButton(client->getImgInd());
}


void MainWindow::on_actionUnirse_triggered()
{
    client = new clientSock;
    client->startClient();

    // Solicitar nombre
    std::string name = "";
    QTextStream out(stdout);
    while(name == "") {
        name = (QInputDialog::getText(this, "Nombre", "Ingrese su nombre:")).toStdString();
        if (name.length() == 0) {
            QMessageBox::about(this, "Error", "Su nombre está vacío");
            name = "";
        }
        if (name.length() >= 15) {
            QMessageBox::about(this, "Error", "Su nombre es muy largo");
            name = "";
        }
    }

    char* nameChar = (char*)name.c_str();

    //std::string nameSend = "name-";
    //nameSend.append(name);
    //char* nameSendChar = (char*)nameSend.c_str()

    // Almacenamiento de datos del juego.
    game = new Game;
    game->setPlayerName(nameChar);

    // Enviar nombre
    client->sendMessage("name", 4);
    //client->sendMessage("-", 4);
    client->sendMessage(nameChar, strlen(nameChar));


    printf("%s", game->getPlayerName());

    // Desactivar el menu bar.
    ui->menubar->setEnabled(false);

    // Colocar nombre en pantalla
    ui->playerNameLabel->setText(QString::fromStdString(name));

    // Obtener el nombre del enemigo para mostrarlo en pantalla.
    ui->infoGameLabel->setText("Esperando jugador...");
    std::thread tEnemyName(&MainWindow::waitEnemyName, this);
    tEnemyName.detach();
}

void MainWindow::gameTurn() {   
    if (client->getPlayable()) {
        ui->infoGameLabel->setText("Esperando...");
        while (!client->getTurn()) {
            sleep_for(std::chrono::milliseconds(100));
        }
        changeEnabledButton(true);
        ui->infoGameLabel->setText("¡Es tu turno!");
    }
}

void MainWindow::gameStarted() {
    while (!client->getPlayable()) {
        sleep_for(std::chrono::milliseconds(200));
    }
    ui->infoGameLabel->setText("Juego iniciado");
    std::thread tTime(&MainWindow::time, this);
    tTime.detach();
    gameTurn(); 

}

void MainWindow::waitIndicatorCards() {
    while (!client->getImgIndBool()) {
        sleep_for(std::chrono::milliseconds(200));
    }
    char* imageQuestion = client->getImgInd();
    changeAllImageButton(imageQuestion);
    //ui->infoGameLabel->setText(" ");
    gameStarted();
}


void MainWindow::waitEnemyName() {
    while (!client->getEnemyNameReceived()) {
        sleep_for(std::chrono::milliseconds(200));
    }
    char* enemyName = client->getEnemyName();
    ui->enemyNameLabel->setText(enemyName);
    ui->infoGameLabel->setText("Cargando...");
    waitIndicatorCards();

}



void MainWindow::on_pushButton_2_clicked()
{
    std::thread time(&MainWindow::time, this);
    time.detach();
}



void MainWindow::waitCard() {
    QPushButton *buttons[30] = {ui->card00, ui->card01, ui->card02, ui->card03, ui->card04, ui->card05,
                                ui->card10, ui->card11, ui->card12, ui->card13, ui->card14, ui->card15,
                                ui->card20, ui->card21, ui->card22, ui->card23, ui->card24, ui->card25,
                                ui->card30, ui->card31, ui->card32, ui->card33, ui->card34, ui->card35,
                                ui->card40, ui->card41, ui->card42, ui->card43, ui->card44, ui->card45};
    while (!client->getNewData()) {
        sleep_for(std::chrono::milliseconds(100));
    }
    changeImageButton(client->getData(), buttons[this->lastCardSelected]);
    client->clearData();
    client->setNewData(false);
}


void MainWindow::on_card00_clicked()
{
    this->lastCardSelected = 0;
    client->sendMessage("card", 4);
    client->sendMessage(" ", 100);

    std::thread tWaitCard(&MainWindow::waitCard, this);
    tWaitCard.detach();
}

