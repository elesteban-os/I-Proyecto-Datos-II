#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include "memory.h"
#include <thread>
#include <string>
#include <stdio.h>
#include <string.h>

using std::this_thread::sleep_for;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeMemoryUsage();
    void changeMemoryUsageHelper();

private slots:
    void on_startServerBtn_clicked();
    void on_sendImgBtn_clicked();

private:
    Ui::MainWindow *ui;
    Server *server;
    Memory memoryManager;
};
#endif // MAINWINDOW_H
