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
    QLabel *staticMemoryUsage;
    QLabel *variableMemoryUsage;
    QTableWidget *tableWidget;
    QLabel *staticPages;
    QLabel *staticPageHit;
    QLabel *staticPageFault;
    QLabel *pageHit;
    QLabel *pageFault;
    QLabel *staticPoints;
    QLabel *staticName1;
    QLabel *staticName2;
    QLabel *points1;
    QLabel *points2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(471, 575);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        startServerBtn = new QPushButton(centralwidget);
        startServerBtn->setObjectName(QString::fromUtf8("startServerBtn"));
        startServerBtn->setGeometry(QRect(190, 180, 101, 24));
        logText = new QPlainTextEdit(centralwidget);
        logText->setObjectName(QString::fromUtf8("logText"));
        logText->setGeometry(QRect(20, 20, 431, 141));
        staticMemoryUsage = new QLabel(centralwidget);
        staticMemoryUsage->setObjectName(QString::fromUtf8("staticMemoryUsage"));
        staticMemoryUsage->setGeometry(QRect(180, 210, 131, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        staticMemoryUsage->setFont(font);
        staticMemoryUsage->setAlignment(Qt::AlignCenter);
        variableMemoryUsage = new QLabel(centralwidget);
        variableMemoryUsage->setObjectName(QString::fromUtf8("variableMemoryUsage"));
        variableMemoryUsage->setGeometry(QRect(185, 240, 120, 16));
        variableMemoryUsage->setAlignment(Qt::AlignCenter);
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(15, 290, 431, 71));
        tableWidget->setRowCount(1);
        tableWidget->horizontalHeader()->setDefaultSectionSize(190);
        staticPages = new QLabel(centralwidget);
        staticPages->setObjectName(QString::fromUtf8("staticPages"));
        staticPages->setGeometry(QRect(125, 260, 240, 31));
        staticPages->setFont(font);
        staticPages->setAlignment(Qt::AlignCenter);
        staticPageHit = new QLabel(centralwidget);
        staticPageHit->setObjectName(QString::fromUtf8("staticPageHit"));
        staticPageHit->setGeometry(QRect(130, 370, 91, 31));
        staticPageHit->setFont(font);
        staticPageHit->setAlignment(Qt::AlignCenter);
        staticPageFault = new QLabel(centralwidget);
        staticPageFault->setObjectName(QString::fromUtf8("staticPageFault"));
        staticPageFault->setGeometry(QRect(280, 370, 91, 31));
        staticPageFault->setFont(font);
        staticPageFault->setAlignment(Qt::AlignCenter);
        pageHit = new QLabel(centralwidget);
        pageHit->setObjectName(QString::fromUtf8("pageHit"));
        pageHit->setGeometry(QRect(130, 390, 91, 31));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        pageHit->setFont(font1);
        pageHit->setAlignment(Qt::AlignCenter);
        pageFault = new QLabel(centralwidget);
        pageFault->setObjectName(QString::fromUtf8("pageFault"));
        pageFault->setGeometry(QRect(280, 390, 91, 31));
        pageFault->setFont(font1);
        pageFault->setAlignment(Qt::AlignCenter);
        staticPoints = new QLabel(centralwidget);
        staticPoints->setObjectName(QString::fromUtf8("staticPoints"));
        staticPoints->setGeometry(QRect(200, 430, 91, 31));
        staticPoints->setFont(font);
        staticPoints->setAlignment(Qt::AlignCenter);
        staticName1 = new QLabel(centralwidget);
        staticName1->setObjectName(QString::fromUtf8("staticName1"));
        staticName1->setGeometry(QRect(130, 460, 91, 31));
        staticName1->setFont(font);
        staticName1->setAlignment(Qt::AlignCenter);
        staticName2 = new QLabel(centralwidget);
        staticName2->setObjectName(QString::fromUtf8("staticName2"));
        staticName2->setGeometry(QRect(280, 460, 91, 31));
        staticName2->setFont(font);
        staticName2->setAlignment(Qt::AlignCenter);
        points1 = new QLabel(centralwidget);
        points1->setObjectName(QString::fromUtf8("points1"));
        points1->setGeometry(QRect(130, 480, 91, 31));
        points1->setFont(font1);
        points1->setAlignment(Qt::AlignCenter);
        points2 = new QLabel(centralwidget);
        points2->setObjectName(QString::fromUtf8("points2"));
        points2->setGeometry(QRect(280, 480, 91, 31));
        points2->setFont(font1);
        points2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 471, 21));
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
        staticMemoryUsage->setText(QCoreApplication::translate("MainWindow", "Memoria en uso", nullptr));
        variableMemoryUsage->setText(QCoreApplication::translate("MainWindow", "0 Bytes", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Memoria", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Disco", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "P\303\241ginas", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        staticPages->setText(QCoreApplication::translate("MainWindow", "P\303\241ginas", nullptr));
        staticPageHit->setText(QCoreApplication::translate("MainWindow", "Page Hit", nullptr));
        staticPageFault->setText(QCoreApplication::translate("MainWindow", "Page Fault", nullptr));
        pageHit->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pageFault->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        staticPoints->setText(QCoreApplication::translate("MainWindow", "Puntajes", nullptr));
        staticName1->setText(QCoreApplication::translate("MainWindow", "Nombre", nullptr));
        staticName2->setText(QCoreApplication::translate("MainWindow", "Nombre", nullptr));
        points1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        points2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
