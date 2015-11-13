#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include <QFileDialog>
#include <QString>
#include <QCheckBox>
#include<QVBoxLayout>
#include <fstream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cbMNT=NULL;
    cbGPX=NULL;

   /* ui->widgetZoneVisu->leMnt=new Mnt();

    ui->widgetZoneVisu->leMnt->loadMnt("//home//gtsi//DDDgpx//Ecrins2.xyz");

    //4-Retrouver les triangles de dalle à partir des points de la dalle : leMnt->setTriangles();

//1-Trouver les deux points délimitant la dalle leMnt-> ; leMnt->CalculateMaxDalle(maxBounds);
//2-Construire la dalle : leMnt->dalle.setBounds(p1,p2);

//ui->widgetZoneVisu->leMnt->CalculateBoundsDalle(BoundsMin,BoundsMax);

//3-Définir les indices du maillage de la dalle : leMnt.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           Dalle();

ui->widgetZoneVisu->leGpx=new gpx();
ui->widgetZoneVisu->leGpx->loadGpx("");
ui->widgetZoneVisu->leGpx->minlat=BoundsMin.y;
ui->widgetZoneVisu->leGpx->minlon=BoundsMin.x;
ui->widgetZoneVisu->leGpx->maxlat=BoundsMax.y;
ui->widgetZoneVisu->leGpx->maxlon=BoundsMax.x;
ui->widgetZoneVisu->leGpx->CalculateBoundsDalle(*(ui->widgetZoneVisu->leMnt));

ui->widgetZoneVisu->leGpx->CalculateIndicePointsDalle(*(ui->widgetZoneVisu->leMnt));

ui->widgetZoneVisu->leGpx->BuildTriangles(*(ui->widgetZoneVisu->leMnt));*/

}

void MainWindow::on_Action_ouvrirMNT_triggered()
{


    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open MNT"), "/home/gtsi/DDDgpx/", tr("All files  (*.xyz)"));
    if(fileName=="") return;

    cbMNT=new QCheckBox(fileName,this);

    cbMNT->move(10,100);
    cbMNT->show();
    //récupération des coordonnées des points à partir du fichier chargé
    //ui->widgetZoneVisu->loadMnt();

    ui->widgetZoneVisu->leMnt=new Mnt();

    ui->widgetZoneVisu->leMnt->loadMnt(fileName.toStdString());


}

void MainWindow::on_actionOuvrir_GPX_triggered()
{

    if(ui->widgetZoneVisu->leMnt==NULL) return;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open MNT"), "/home/gtsi/DDDgpx/", tr("All files  (*.gpx)"));
    if(fileName=="") return;

    cbGPX=new QCheckBox(fileName,this);

    cbGPX->move(10,120);
    cbGPX->show();
    //récupération des coordonnées des points à partir du fichier chargé
    //ui->widgetZoneVisu->loadMnt();


    //bounds de GPX : voir Romain...
        Point BoundsMin;
        BoundsMin.x=0.1;
                //900111
                //;
                //;
                //980000
        BoundsMin.y=-0.75;
                //1900026
                //;
                //;
                //1904000
        Point BoundsMax;
        BoundsMax.x= 0.9;
                //900511
                //;
                //;
                //990000
                ////
        BoundsMax.y= -0.1;
                //1900126
                //;
                //;
                //1940000
                ////
        ui->widgetZoneVisu->leGpx=new gpx();
        ui->widgetZoneVisu->leGpx->loadGpx("");
        ui->widgetZoneVisu->leGpx->minlat=BoundsMin.y;
        ui->widgetZoneVisu->leGpx->minlon=BoundsMin.x;
        ui->widgetZoneVisu->leGpx->maxlat=BoundsMax.y;
        ui->widgetZoneVisu->leGpx->maxlon=BoundsMax.x;
        ui->widgetZoneVisu->leGpx->CalculateBoundsDalle(*(ui->widgetZoneVisu->leMnt));

        ui->widgetZoneVisu->leGpx->CalculateIndicePointsDalle(*(ui->widgetZoneVisu->leMnt));

        ui->widgetZoneVisu->leGpx->BuildTriangles(*(ui->widgetZoneVisu->leMnt));
        //Construire la trajectoire
        ui->widgetZoneVisu->leGpx->CalculateTrajectoire(*(ui->widgetZoneVisu->leMnt));

        //
        ui->widgetZoneVisu->gentilhomme = new Randonneur();
        ui->widgetZoneVisu->gentilhomme->randonnee=ui->widgetZoneVisu->leGpx->trajectoire;
        //ui->widgetZoneVisu->gentilhomme->init();


}

MainWindow::~MainWindow()
{
    delete cbMNT;
    delete cbGPX;
    delete ui;

}
