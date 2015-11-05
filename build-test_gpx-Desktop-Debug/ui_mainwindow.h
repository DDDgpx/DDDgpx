/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <simpleviewer.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *Action_ouvrirMNT;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    SimpleViewer *widgetZoneVisu;
    QMenuBar *menuBar;
    QMenu *menuOuvrir;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(598, 445);
        Action_ouvrirMNT = new QAction(MainWindow);
        Action_ouvrirMNT->setObjectName(QStringLiteral("Action_ouvrirMNT"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 30, 181, 171));
        widgetZoneVisu = new SimpleViewer(centralWidget);
        widgetZoneVisu->setObjectName(QStringLiteral("widgetZoneVisu"));
        widgetZoneVisu->setGeometry(QRect(200, 30, 371, 331));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 598, 29));
        menuOuvrir = new QMenu(menuBar);
        menuOuvrir->setObjectName(QStringLiteral("menuOuvrir"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOuvrir->menuAction());
        menuOuvrir->addAction(Action_ouvrirMNT);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Action_ouvrirMNT->setText(QApplication::translate("MainWindow", "Ouvrir mnt", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Liste des fichiers charg\303\251s", 0));
        menuOuvrir->setTitle(QApplication::translate("MainWindow", "ouvrir", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
