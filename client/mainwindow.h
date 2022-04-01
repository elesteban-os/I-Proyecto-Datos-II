#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientsock.h"
#include <string.h>

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

private slots:
    void on_connectBtn_clicked();
    void on_seeImageBtn_clicked();

private:
    Ui::MainWindow *ui;
    clientSock *client;
};
#endif // MAINWINDOW_H
