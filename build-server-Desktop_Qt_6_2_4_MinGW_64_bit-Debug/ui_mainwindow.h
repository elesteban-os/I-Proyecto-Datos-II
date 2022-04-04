/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *startServerBtn;
    QPlainTextEdit *logText;
    QPushButton *sendImgBtn;
    QLabel *label1;
    QLabel *staticMemoryUsage;
    QLabel *variableMemoryUsage;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(342, 702);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        startServerBtn = new QPushButton(centralwidget);
        startServerBtn->setObjectName(QString::fromUtf8("startServerBtn"));
        startServerBtn->setGeometry(QRect(30, 180, 101, 24));
        logText = new QPlainTextEdit(centralwidget);
        logText->setObjectName(QString::fromUtf8("logText"));
        logText->setGeometry(QRect(20, 20, 291, 141));
        sendImgBtn = new QPushButton(centralwidget);
        sendImgBtn->setObjectName(QString::fromUtf8("sendImgBtn"));
        sendImgBtn->setGeometry(QRect(220, 180, 91, 24));
        label1 = new QLabel(centralwidget);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(40, 420, 201, 201));
        staticMemoryUsage = new QLabel(centralwidget);
        staticMemoryUsage->setObjectName(QString::fromUtf8("staticMemoryUsage"));
        staticMemoryUsage->setGeometry(QRect(190, 210, 131, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        staticMemoryUsage->setFont(font);
        variableMemoryUsage = new QLabel(centralwidget);
        variableMemoryUsage->setObjectName(QString::fromUtf8("variableMemoryUsage"));
        variableMemoryUsage->setGeometry(QRect(190, 240, 121, 16));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 2)
            tableWidget->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 220, 171, 101));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 342, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startServerBtn->setText(QCoreApplication::translate("MainWindow", "Iniciar Servidor", nullptr));
        sendImgBtn->setText(QCoreApplication::translate("MainWindow", "Enviar Imagen", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        staticMemoryUsage->setText(QCoreApplication::translate("MainWindow", "Memoria en uso", nullptr));
        variableMemoryUsage->setText(QCoreApplication::translate("MainWindow", "0 Bytes", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "P\303\241ginas", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Memoria", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Disco", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
