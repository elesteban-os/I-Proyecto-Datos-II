#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientsock.h"
#include <thread>
#include <string.h>
#include <iostream>

/**
 * @brief Construct a new Main Window:: Main Window object.
 * 
 * @param parent 
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pu1->setToolTip("Tendrás un 50% de posibilidades de encontrar un par. Tienes 2, ¡Usalos bien!");
    ui->pu2->setToolTip("No se reordenarán las tarjetas durante tres rondas. ¡Afecta al oponente!. Tienes 2, ¡Usalos bien!");
    ui->pu3->setToolTip("Obtendrás el doble de puntaje si eliges correctarmente el par. Tienes 2, ¡Usalos bien!");
}

/**
 * @brief Destroy the Main Window:: Main Window object.
 * 
 */
MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * @brief Realiza un thread para el conteo del tiempo.
 * 
 */
void MainWindow::timeHelper() {
    std::thread tTime(&MainWindow::time, this);
    tTime.detach();
}

/**
 * @brief Lógica de reloj y cambia los valores en pantalla.
 * 
 */
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

/**
 * @brief Obtiene un dato desde el cliente.
 * 
 */
void MainWindow::threadData() {
    while (1) {
        std::cout << (client->getData());
    }
}

/**
 * @brief Cambia la imagen de un boton.
 * 
 * @param image puntero de un char array de una imagen.
 * @param button botón al que se le va a cambiar la imagen. 
 */
void MainWindow::changeImageButton(char *image, QPushButton* button) {
    QImage imgdata((uchar*)image, 100, 100, QImage::Format_ARGB32);
    QPixmap p(QPixmap::fromImage(imgdata));
    button->setIcon(p);
    button->setIconSize(QSize(100, 100));
}

/**
 * @brief Coloca un valor de actividad de todos los botones.
 * 
 * @param enabled Valor de actividad.
 */
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

/**
 * @brief Coloca una imagen a todos los botones.
 * 
 * @param image char array de la imagen.
 */
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

/**
 * @brief Obtiene un valor desde el cliente para saber si todo está listo para empezar a jugar.
 * 
 */
void MainWindow::isPlayable() {
    while (!client->getPlayable()) {
        sleep_for(std::chrono::milliseconds(1000));
    }
    game->setOpponentName(client->getEnemyName());
    changeAllImageButton(client->getImgInd());
}

/**
 * @brief Realiza los preparativos para unirse a un juego.
 * 
 */
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

    std::thread tEnemyPoints(&MainWindow::waitEnemyPoints, this);
    tEnemyPoints.detach();
}

/**
 * @brief Obtiene el turno desde el cliente.
 * 
 */
void MainWindow::gameTurn() {   
    if (client->getPlayable()) {
        ui->infoGameLabel->setText("Esperando...");
        while (!client->getTurn()) {
            sleep_for(std::chrono::milliseconds(100));
        }
        changeEnabledButton(true);
        ui->infoGameLabel->setText("¡Es tu turno!");
        setPUEnabled(true);
    }
}

/**
 * @brief Obtiene la indicación de la inicializción del juego.
 * 
 */
void MainWindow::gameStarted() {
    while (!client->getPlayable()) {
        sleep_for(std::chrono::milliseconds(200));
    }
    ui->infoGameLabel->setText("Juego iniciado");
    std::thread tTime(&MainWindow::time, this);
    tTime.detach();
    gameTurn(); 

}

/**
 * @brief Obtiene las cartas indicadoras que el servidor envía.
 * 
 */
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

/**
 * @brief Obtiene el nombre del oponente.
 * 
 */
void MainWindow::waitEnemyName() {
    while (!client->getEnemyNameReceived()) {
        sleep_for(std::chrono::milliseconds(200));
    }
    char* enemyName = client->getEnemyName();
    ui->enemyNameLabel->setText(enemyName);
    ui->infoGameLabel->setText("Cargando...");
    waitIndicatorCards();

}

/**
 * @brief Obtiene el valor de una carta indicadora.
 * 
 */
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

/**
 * @brief Analiza los resultados las cartas seleccionadas.
 * 
 * @param result Resultado de las cartas seleccionadas.
 */
void MainWindow::analizeResults(bool result) {

    if (result) {
        // Obtener indicador y puntaje, hacer inactivas algunas cartas.
        getNewCardIndicator();
        enabledButtons[lastCardSelected[0]][lastCardSelected[1]] = 0;
        enabledButtons[lastCardSelected2[0]][lastCardSelected2[1]] = 0;

        while (client->getPoints() == -1) {
            sleep_for(std::chrono::milliseconds(10));
        }

        int points = client->getPoints();
        game->addScore(0, points);
        ui->points->display(points);
        client->setPoints(-1);
        client->setPlayerPoints(-1);

    } else {
        getNewCardIndicator();
    }
    lastCardSelected[0] = -1;
    lastCardSelected2[0] = -1;
    lastCardSelected[1] = -1;
    lastCardSelected2[1] = -1;
    lastNumCardSelected = -1;
    client->setTurn(false);
    changeEnabledButton(false);
    setPUEnabled(false);
    gameTurn();
}

/**
 * @brief Verifica el par elegido con la comunicación con el server.
 * 
 */
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

/**
 * @brief Obtiene las carta elegidas por el oponente para observarlas en el juego.
 * 
 */
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

/**
 * @brief Espera el puntaje obtenido por el oponente.
 */
void MainWindow::waitEnemyPoints() {
    while (1) {
        while (client->getPlayerPoints() != 1) {
            sleep_for(std::chrono::milliseconds(100));
        }
        sleep_for(std::chrono::milliseconds(200));
        int points = client->getPoints();
        game->addScore(1, points);
        ui->enemyPoints->display(points);
        client->setPoints(-1);
        client->setPlayerPoints(-1);

    }
}

/**
 * @brief Obtiene la imagen del botón seleccionado.
 * 
 */
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

/**
 * @brief Realiza la lógica para verificar pares de una tarjetas y envíos del mensaje.
 * 
 * @param card 
 */
void MainWindow::cardSelectedSystem(int card) {
    int x = card / 10;
    int y = card % 10;
    if (enabledButtons[x][y]) {
        if (lastNumCardSelected != card) {
            if (cardsSelected == 0) {
                lastCardSelected[0] = x;
                lastCardSelected[1] = y;
                setPUEnabled(false);
            } else {
                lastCardSelected2[0] = x;
                lastCardSelected2[1] = y;
            }
            lastNumCardSelected = card;
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

/**
 * @brief Habilita o deshabilita los botones de los powerups.
 * @param valor.
 */
void MainWindow::setPUEnabled(bool value) {
    QPushButton *puButtons[3] = {ui->pu1, ui->pu2, ui->pu3};
    if (value) {
        for (int i = 0; i < 3; i++) {
            if (availablePU[i] != 0) {
                puButtons[i]->setEnabled(value);
            }
        }
    } else {
        for (QPushButton *b : puButtons) {
            b->setEnabled(value);
        }
    }
}


/**
 * @brief Función que hace la acción del botón del primer powerup.
 */
void MainWindow::on_pu1_clicked()
{
    client->sendMessage("pu1", 3);
    ui->pu1->setEnabled(false);
    availablePU[0]--;

}

/**
 * @brief Función que hace la acción del botón del segundo powerup.
 */
void MainWindow::on_pu2_clicked()
{
    client->sendMessage("pu2", 3);
    ui->pu2->setEnabled(false);
    availablePU[1]--;
}

/**
 * @brief Función que hace la acción del botón del tercer powerup.
 */
void MainWindow::on_pu3_clicked()
{
    client->sendMessage("pu3", 3);
    ui->pu3->setEnabled(false);
    availablePU[2]--;
}


/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 00.
 * 
 */
void MainWindow::on_card00_clicked()
{
    cardSelectedSystem(0);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 01.
 *
 */
void MainWindow::on_card01_clicked()
{
    cardSelectedSystem(1);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 02.
 *
 */
void MainWindow::on_card02_clicked()
{
    cardSelectedSystem(2);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 03.
 *
 */
void MainWindow::on_card03_clicked()
{
    cardSelectedSystem(3);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 04.
 *
 */
void MainWindow::on_card04_clicked()
{
    cardSelectedSystem(4);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 05.
 *
 */
void MainWindow::on_card05_clicked()
{
    cardSelectedSystem(5);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 10.
 *
 */
void MainWindow::on_card10_clicked()
{
    cardSelectedSystem(10);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 11.
 *
 */
void MainWindow::on_card11_clicked()
{
    cardSelectedSystem(11);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 12.
 *
 */
void MainWindow::on_card12_clicked()
{
    cardSelectedSystem(12);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 13.
 *
 */
void MainWindow::on_card13_clicked()
{
    cardSelectedSystem(13);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 14.
 *
 */
void MainWindow::on_card14_clicked()
{
    cardSelectedSystem(14);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 15.
 *
 */
void MainWindow::on_card15_clicked()
{
    cardSelectedSystem(15);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 20.
 *
 */
void MainWindow::on_card20_clicked()
{
    cardSelectedSystem(20);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 21.
 *
 */
void MainWindow::on_card21_clicked()
{
    cardSelectedSystem(21);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 22.
 *
 */
void MainWindow::on_card22_clicked()
{
    cardSelectedSystem(22);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 23.
 *
 */
void MainWindow::on_card23_clicked()
{
    cardSelectedSystem(23);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 24.
 *
 */
void MainWindow::on_card24_clicked()
{
    cardSelectedSystem(24);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 25.
 *
 */
void MainWindow::on_card25_clicked()
{
    cardSelectedSystem(25);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 30.
 *
 */
void MainWindow::on_card30_clicked()
{
    cardSelectedSystem(30);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 31.
 *
 */
void MainWindow::on_card31_clicked()
{
    cardSelectedSystem(31);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 32.
 *
 */
void MainWindow::on_card32_clicked()
{
    cardSelectedSystem(32);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 33.
 *
 */
void MainWindow::on_card33_clicked()
{
    cardSelectedSystem(33);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 34.
 *
 */
void MainWindow::on_card34_clicked()
{
    cardSelectedSystem(34);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 35.
 *
 */
void MainWindow::on_card35_clicked()
{
    cardSelectedSystem(35);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 40.
 *
 */
void MainWindow::on_card40_clicked()
{
    cardSelectedSystem(40);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 41.
 *
 */
void MainWindow::on_card41_clicked()
{
    cardSelectedSystem(41);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 42.
 *
 */
void MainWindow::on_card42_clicked()
{
    cardSelectedSystem(42);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 43.
 *
 */
void MainWindow::on_card43_clicked()
{
    cardSelectedSystem(43);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 44.
 *
 */
void MainWindow::on_card44_clicked()
{
    cardSelectedSystem(44);
}

/**
 * @brief Indicación de la seleción de una tarjeta en la ubicación 45.
 *
 */
void MainWindow::on_card45_clicked()
{
    cardSelectedSystem(45);
}









