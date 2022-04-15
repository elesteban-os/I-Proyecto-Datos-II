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

void MainWindow::timeHelper() {
    std::thread tTime(&MainWindow::time, this);
    tTime.detach();
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

    std::thread tWaitCard(&MainWindow::waitCard, this);
    tWaitCard.detach();

    std::thread tEnemyWaitCard(&MainWindow::waitEnemyCardSelected, this);
    tEnemyWaitCard.detach();
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
    client->setImgIndBool(false);
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


void MainWindow::getNewCardIndicator() {
    QPushButton *buttons[5][6] = {{ui->card00, ui->card01, ui->card02, ui->card03, ui->card04, ui->card05},
                                  {ui->card10, ui->card11, ui->card12, ui->card13, ui->card14, ui->card15},
                                  {ui->card20, ui->card21, ui->card22, ui->card23, ui->card24, ui->card25},
                                  {ui->card30, ui->card31, ui->card32, ui->card33, ui->card34, ui->card35},
                                  {ui->card40, ui->card41, ui->card42, ui->card43, ui->card44, ui->card45}};
    while (!client->getImgIndBool()) {
        sleep_for(std::chrono::milliseconds(100));
    }
    char* imageResult = client->getImgInd();
    changeImageButton(imageResult, buttons[lastCardSelected[0]][lastCardSelected[1]]);
    //sleep_for(std::chrono::milliseconds(10));
    changeImageButton(imageResult, buttons[lastCardSelected2[0]][lastCardSelected2[1]]);
    client->setImgIndBool(false);
}

void MainWindow::analizeResults(bool result) {

    if (result) {
        // Obtener indicador y puntaje, hacer inactivas algunas cartas.
        getNewCardIndicator();
        enabledButtons[lastCardSelected[0]][lastCardSelected[1]] = 0;
        enabledButtons[lastCardSelected2[0]][lastCardSelected2[1]] = 0;
    } else {
        getNewCardIndicator();
    }
    lastCardSelected[0] = -1;
    lastCardSelected2[0] = -1;
    client->setTurn(false);
    changeEnabledButton(false);
    gameTurn();
}

void MainWindow::verifyPair() {
    if (cardsSelected == 2) {
        while (client->getCorrect() == -1) {
            sleep_for(std::chrono::milliseconds(100));
        }
        if (client->getCorrect() == 1) {
            qDebug() << "par encontrado";
            analizeResults(true);

        } else {
            qDebug() << "par no encontrado";
            analizeResults(false);
        }
        client->setCorrect(-1);
        cardsSelected = 0;
    }
}

void MainWindow::waitEnemyCardSelected() {
    QPushButton *buttons[5][6] = {{ui->card00, ui->card01, ui->card02, ui->card03, ui->card04, ui->card05},
                                  {ui->card10, ui->card11, ui->card12, ui->card13, ui->card14, ui->card15},
                                  {ui->card20, ui->card21, ui->card22, ui->card23, ui->card24, ui->card25},
                                  {ui->card30, ui->card31, ui->card32, ui->card33, ui->card34, ui->card35},
                                  {ui->card40, ui->card41, ui->card42, ui->card43, ui->card44, ui->card45}};
    int x;
    int y;
    while (1) {
        while (!client->getEnemyDataReceived()) {
            sleep_for(std::chrono::milliseconds(100));
        }
        x = client->getEnemyCardLocation() / 10;
        y = client->getEnemyCardLocation() % 10;
        bool cardFound = client->getCorrectEnemyCardSelected();
        changeImageButton(client->getData(), buttons[x][y]);
        if (cardFound) {
            enabledButtons[x][y] = 0;
        }

        client->clearData();
        client->setEnemyDataReceived(false);
    }

}

void MainWindow::waitCard() {
    QPushButton *buttons[5][6] = {{ui->card00, ui->card01, ui->card02, ui->card03, ui->card04, ui->card05},
                                  {ui->card10, ui->card11, ui->card12, ui->card13, ui->card14, ui->card15},
                                  {ui->card20, ui->card21, ui->card22, ui->card23, ui->card24, ui->card25},
                                  {ui->card30, ui->card31, ui->card32, ui->card33, ui->card34, ui->card35},
                                  {ui->card40, ui->card41, ui->card42, ui->card43, ui->card44, ui->card45}};
    while (1) {
        while (!client->getNewData()) {
            sleep_for(std::chrono::milliseconds(100));
        }
        if (lastCardSelected2[0] != -1) {
            changeImageButton(client->getData(), buttons[lastCardSelected2[0]][lastCardSelected2[1]]);
        } else {
            changeImageButton(client->getData(), buttons[lastCardSelected[0]][lastCardSelected[1]]);
        }

        client->clearData();
        client->setNewData(false);
    }

}

void MainWindow::cardSelectedSystem(int card) {
    int x = card / 10;
    int y = card % 10;
    if (enabledButtons[x][y]) {
        if (cardsSelected < 2) {
            if (cardsSelected == 0) {
                lastCardSelected[0] = x;
                lastCardSelected[1] = y;
            } else {
                lastCardSelected2[0] = x;
                lastCardSelected2[1] = y;
            }
            cardsSelected++;
            std::thread tVerify(&MainWindow::verifyPair, this);
            tVerify.detach();
            client->sendMessage("card", 4);
            if (card == 0) {
                client->sendMessage(" ", 100);
            } else {
                client->sendMessage(" ", card);
            }
        }
    }
}

void MainWindow::on_card00_clicked()
{
    cardSelectedSystem(0);
}

void MainWindow::on_card01_clicked()
{
    cardSelectedSystem(1);
}

void MainWindow::on_card02_clicked()
{
    cardSelectedSystem(2);
}

void MainWindow::on_card03_clicked()
{
    cardSelectedSystem(3);
}

void MainWindow::on_card04_clicked()
{
    cardSelectedSystem(4);
}

void MainWindow::on_card05_clicked()
{
    cardSelectedSystem(5);
}

void MainWindow::on_card10_clicked()
{
    cardSelectedSystem(10);
}


void MainWindow::on_card11_clicked()
{
    cardSelectedSystem(11);
}


void MainWindow::on_card12_clicked()
{
    cardSelectedSystem(12);
}


void MainWindow::on_card13_clicked()
{
    cardSelectedSystem(13);
}


void MainWindow::on_card14_clicked()
{
    cardSelectedSystem(14);
}


void MainWindow::on_card15_clicked()
{
    cardSelectedSystem(15);
}


void MainWindow::on_card20_clicked()
{
    cardSelectedSystem(20);
}


void MainWindow::on_card21_clicked()
{
    cardSelectedSystem(21);
}


void MainWindow::on_card22_clicked()
{
    cardSelectedSystem(22);
}


void MainWindow::on_card23_clicked()
{
    cardSelectedSystem(23);
}


void MainWindow::on_card24_clicked()
{
    cardSelectedSystem(24);
}


void MainWindow::on_card25_clicked()
{
    cardSelectedSystem(25);
}


void MainWindow::on_card30_clicked()
{
    cardSelectedSystem(30);
}


void MainWindow::on_card31_clicked()
{
    cardSelectedSystem(31);
}


void MainWindow::on_card32_clicked()
{
    cardSelectedSystem(32);
}


void MainWindow::on_card33_clicked()
{
    cardSelectedSystem(33);
}


void MainWindow::on_card34_clicked()
{
    cardSelectedSystem(34);
}



void MainWindow::on_card35_clicked()
{
    cardSelectedSystem(35);
}


void MainWindow::on_card40_clicked()
{
    cardSelectedSystem(40);
}


void MainWindow::on_card41_clicked()
{
    cardSelectedSystem(41);
}


void MainWindow::on_card42_clicked()
{
    cardSelectedSystem(42);
}


void MainWindow::on_card43_clicked()
{
    cardSelectedSystem(43);
}


void MainWindow::on_card44_clicked()
{
    cardSelectedSystem(44);
}


void MainWindow::on_card45_clicked()
{
    cardSelectedSystem(45);
}

