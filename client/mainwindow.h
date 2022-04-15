#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientsock.h"
#include <string.h>
#include <string>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void threadData();
    void changeImageButton(char* image, QPushButton* button);
    void changeAllImageButton(char* image);
    void changeEnabledButton(bool enabled);
    void changeEnabledOneButton(bool enabled);
    void isPlayable();
    void time();
    void waitEnemyName();
    void waitIndicatorCards();
    void gameStarted();
    void gameTurn();
    void waitCard();
    void waitEnemyCardSelected();
    void verifyPair();
    void analizeResults(bool result);
    void getNewCardIndicator();
    void cardSelectedSystem(int card);
    void timeHelper();

private slots:
    void on_actionUnirse_triggered();

    void on_card00_clicked();

    void on_card01_clicked();    

    void on_card04_clicked();

    void on_card02_clicked();

    void on_card03_clicked();

    void on_card10_clicked();

    void on_card11_clicked();

    void on_card05_clicked();

    void on_card12_clicked();

    void on_card13_clicked();

    void on_card14_clicked();

    void on_card15_clicked();

    void on_card20_clicked();

    void on_card21_clicked();

    void on_card22_clicked();

    void on_card23_clicked();

    void on_card24_clicked();

    void on_card25_clicked();

    void on_card30_clicked();

    void on_card31_clicked();

    void on_card32_clicked();

    void on_card33_clicked();

    void on_card34_clicked();

    void on_card35_clicked();

    void on_card40_clicked();

    void on_card41_clicked();

    void on_card42_clicked();

    void on_card43_clicked();

    void on_card44_clicked();

    void on_card45_clicked();

private:
    Ui::MainWindow *ui;
    clientSock *client;
    Game *game;
    int timeSec0x = 0;
    int timeSecx0 = 0;
    int timeMin0x = 0;
    int timeMinx0 = 0;
    int cardsSelected = 0;
    int lastCardSelected[2] = {-1, -1};
    int lastCardSelected2[2] = {-1, -1};
    bool enabledButtons[5][6] = {{1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1}};

};
#endif // MAINWINDOW_H
