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

private slots:
    void on_connectBtn_clicked();
    void on_seeImageBtn_clicked();
    void on_actionUnirse_triggered();

    void on_pushButton_2_clicked();

    void on_card00_clicked();

private:
    Ui::MainWindow *ui;
    clientSock *client;
    Game *game;
    int timeSec0x = 0;
    int timeSecx0 = 0;
    int timeMin0x = 0;
    int timeMinx0 = 0;
    int cardsSelected = 0;
    int lastCardSelected;

};
#endif // MAINWINDOW_H
