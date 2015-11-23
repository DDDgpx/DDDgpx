#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include <QFileDialog>
#include <QString>
#include <QCheckBox>
#include<QVBoxLayout>
#include <fstream>
#include "help.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cbMNT=NULL;
    cbGPX=NULL;
     cbTexture=NULL;

}

void MainWindow::on_Action_ouvrirMNT_triggered()
{


    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open MNT"), "/home/gtsi/DDDgpx/", tr("All files  (*.xyz)"));
    if(fileName=="") return;

    QRegExp rx("\/"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
        QStringList query = fileName.split(rx);
        QString text=query.at(query.size()-1);
        cbMNT=new QCheckBox(text,this);

    cbMNT->move(10,100);
    cbMNT->show();
    //récupération des coordonnées des points à partir du fichier chargé
    //ui->widgetZoneVisu->loadMnt();

    ui->widgetZoneVisu->leMnt=new Mnt();

    ui->widgetZoneVisu->leMnt->loadMnt(fileName.toStdString());
    QObject::connect(cbMNT, SIGNAL(stateChanged(int)),  this, SLOT(on_cbMNT_stateChanged(int)));

    //help::creerGpx(*(ui->widgetZoneVisu->leMnt));

}

void MainWindow::on_actionOuvrir_GPX_triggered()
{

    if(ui->widgetZoneVisu->leMnt==NULL) return;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open MNT"), "/home/gtsi/DDDgpx/", tr("All files  (*.gpx)"));
    if(fileName=="") return;

    QRegExp rx("\/"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList query = fileName.split(rx);
    QString text=query.at(query.size()-1);


    cbGPX=new QCheckBox(text,this);

    cbGPX->move(10,120);
    cbGPX->show();

    cbTexture=new QCheckBox("Texture",this);
        cbTexture->move(10,140);
        cbTexture->show();

        //récupération des coordonnées des points à partir du fichier chargé
        //ui->widgetZoneVisu->loadMnt();
    QObject::connect(cbGPX, SIGNAL(stateChanged(int)),  this, SLOT(on_cbGPX_stateChanged(int)));
    QObject::connect(cbTexture, SIGNAL(stateChanged(int)),  this, SLOT(on_cbTexture_stateChanged(int)));


    //récupération des coordonnées des points à partir du fichier chargé
    //ui->widgetZoneVisu->loadMnt();




        ui->widgetZoneVisu->leGpx=new gpx();
        ui->widgetZoneVisu->leGpx->loadGpx(fileName);
        ui->widgetZoneVisu->leGpx->CalculateBoundsDalle(*(ui->widgetZoneVisu->leMnt));

        ui->widgetZoneVisu->leGpx->CalculateIndicePointsDalle(*(ui->widgetZoneVisu->leMnt));

        ui->widgetZoneVisu->leGpx->BuildTriangles(*(ui->widgetZoneVisu->leMnt));
        //Construire la trajectoire
        ui->widgetZoneVisu->leGpx->setZGpx(*(ui->widgetZoneVisu->leMnt));


        ui->widgetZoneVisu->updateView( ui->widgetZoneVisu->leGpx);



}

MainWindow::~MainWindow()
{
    delete cbMNT;
    delete cbGPX;
     delete cbTexture;
    delete ui;

}


void MainWindow::on_play_clicked()
{
    if( ui->widgetZoneVisu->leMnt ==NULL)
        return ;
    if(ui->widgetZoneVisu->leGpx ==NULL)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Erreur", "Aucun GPX n'est chargé ! Voulez-vous générer un GPX?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            qDebug() << "Yes was clicked : génération du GPX...";
            help::creerGpx(*(ui->widgetZoneVisu->leMnt));

        }
        else
        {
            qDebug() << "no was *not* clicked";
        }
        return;
    }
    //Construire la trajectoire
    if (ui->widgetZoneVisu->leGpx->trajectoire.empty())
    ui->widgetZoneVisu->leGpx->CalculateTrajectoire(*(ui->widgetZoneVisu->leMnt));


    // creation du rondonneur et affectation de la trajectoire
    ui->widgetZoneVisu->gentilhomme = new Randonneur();
    ui->widgetZoneVisu->gentilhomme->randonnee=ui->widgetZoneVisu->leGpx->trajectoire;
    float valeur=ui->horizontalSlider->value();
    ui->widgetZoneVisu->gentilhomme->saVitesse= valeur/10;
    ui->widgetZoneVisu->updateView(ui->widgetZoneVisu->leGpx);
    ui->widgetZoneVisu->animation_allowded=true;
   // ui->widgetZoneVisu->startAnimation();


}


void MainWindow::on_cbMNT_stateChanged(int arg1)
{
    if(arg1==2) //checked
        ui->widgetZoneVisu->leMnt->isDisplayed=true;
    else
         ui->widgetZoneVisu->leMnt->isDisplayed=false;
    ui->widgetZoneVisu->updateView( ui->widgetZoneVisu->gpx_dalle_mnt);
}
void MainWindow::on_cbTexture_stateChanged(int arg1)
{
    if(arg1==2) //checked
        ui->widgetZoneVisu->leGpx->textureActivated=true;
    else
        ui->widgetZoneVisu->leGpx->textureActivated=false;

    ui->widgetZoneVisu->updateView( ui->widgetZoneVisu->gpx_dalle_mnt);
}
void MainWindow::on_cbGPX_stateChanged(int arg1)
{
    if(arg1==2) //checked
        ui->widgetZoneVisu->leGpx->isDisplayed=true;
    else
         ui->widgetZoneVisu->leGpx->isDisplayed=false;
     ui->widgetZoneVisu->updateView(ui->widgetZoneVisu->leGpx);
}


