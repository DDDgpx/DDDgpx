#include "gpx.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QFile>
#include "help.h"
#include <iostream>
#include <string.h>

using namespace std;

gpx::gpx()
{


}
void gpx::loadGpx(std::string fileName){

    double lat=0;
    double lon = 0;
    double ele = 0;
    QString qfileName=QString::fromStdString(fileName);
    QFile file(qfileName);
    QString name = "";
    vector<Point> kk;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open error:" << file.errorString();
    }
    QXmlStreamReader inputStream(&file);
    while (!inputStream.atEnd() && !inputStream.hasError())
    {
        inputStream.readNext();
        name = inputStream.name().toString();
        if (inputStream.isStartElement() && name == "trkpt") {
            lat = inputStream.attributes().value("lat").toFloat();
            lon = inputStream.attributes().value("lon").toFloat();
            while (!(inputStream.isEndElement()) || (name != "trkpt")) {
                inputStream.readNext();
                name = inputStream.name().toString();
                if (inputStream.isStartElement() && name == "ele"){
                    ele = inputStream.readElementText().toFloat();
                    //help::convertCoord(lon, lat);
                    Point p;
                    p.setX(lon);
                    p.setY(lat);
                    p.setZ(ele);
                    kk.push_back(p);
                    ptsGpx.push_back(p);
                    cout<<"un point dans le gpx"<<endl;
                }
            }
        }
        else if (name=="bounds") {
                minlat = inputStream.attributes().value("minlat").toFloat();
                minlon = inputStream.attributes().value("minlon").toFloat();
                maxlat = inputStream.attributes().value("maxlat").toFloat();
                maxlon = inputStream.attributes().value("maxlon").toFloat();
            }
    }
    for(int i=0; i<ptsGpx.size();i++){
        cout<< ptsGpx[i].getX()<< " " << ptsGpx[i].getY()<< " " << ptsGpx[i].getZ()<<endl;
    }
}

Triangle gpx::troisLesPlusProches(Mnt& unMnt, Point p) {
    int i = 0;
    while(!estDansTriangle(p, unMnt, i)) {
        i++;
    }
    cout << unMnt.lesTriangles[i].id_Sommet1 << endl << unMnt.lesTriangles[i].id_Sommet2 << endl << unMnt.lesTriangles[i].id_Sommet3 << endl;
    return unMnt.lesTriangles[i];
}
bool gpx::estDansTriangle(Point p, Mnt& unMnt, int i) {
    if (i%2==0) {
        return conditionDansTrianglePair(p, unMnt, i);
    }
    else {
        return conditionDansTriangleImpair(p, unMnt, i);
    }
}
bool gpx::conditionDansTrianglePair(Point p, Mnt& mnt, int i) {
    Point p2 = mnt.lesPoints[mnt.lesTriangles[i].id_Sommet2 - 1];
    Point p3 = mnt.lesPoints[mnt.lesTriangles[i].id_Sommet3 - 1];
    return (    ( p.getX() > p3.getX() )
             && ( p.getY() < p2.getY() )
             && ( p.getX() < p2.getX() )
             && ( p.getY() > p3.getY() )
             && (mnt.pasX * p.getY() - mnt.pasY * p.getX() > mnt.pasX * p2.getY() - mnt.pasY * p2.getX() ) );
}
bool gpx::conditionDansTriangleImpair(Point p, Mnt& mnt, int i) {
    Point p1 = mnt.lesPoints[mnt.lesTriangles[i].id_Sommet1 - 1];
    Point p2 = mnt.lesPoints[mnt.lesTriangles[i].id_Sommet2 - 1];
    return (    ( p.getX() > p2.getX() )
             && ( p.getY() < p1.getY() )
             && ( p.getX() < p1.getX() )
             && ( p.getY() > p2.getY() )
             && (mnt.pasX * p.getY() - mnt.pasY * p.getX() < mnt.pasX * p2.getY() - mnt.pasY * p2.getX() ) );
}

//méthodes Hanane
void gpx::CalculateBoundsDalle( Mnt &unMnt) //initialize dalle.debut et fin
{
    //initialisation des points bounds
    Point minBounds, maxBounds;
            //ICI conversion des latitudes et longitudes à faire!!!!!!!
    minBounds.x=minlon;
    minBounds.y=minlat;

    maxBounds.x=maxlon;
    maxBounds.y=maxlat;

    //initialisation du debut de la dalle : par défaut c'est le début de MNT
    gpx_dalle.debut.id_point= -1;
    gpx_dalle.debut.x= unMnt.lesPoints[0].x;
    gpx_dalle.debut.y= unMnt.lesPoints[0].y;
    //initialisation de la fin de la dalle : par défaut c'est la fin de MNT
    gpx_dalle.fin.id_point= -1;
    gpx_dalle.fin.x= unMnt.lesPoints[unMnt.lesPoints.size()-1].x;
    gpx_dalle.fin.y= unMnt.lesPoints[unMnt.lesPoints.size()-1].y;
    //algo: Depart.x<minBounds.x et Depart.x est le plus grand possible (idem pour y)
    for(int i=0; i< unMnt.lesPoints.size();i++)
    {
        if(unMnt.lesPoints[i].x <= minBounds.x && unMnt.lesPoints[i].y>= maxBounds.y && unMnt.lesPoints[i].x>= gpx_dalle.debut.x && unMnt.lesPoints[i].y<= gpx_dalle.debut.y)

            {// remplace le point depart de dalle par le point de mnt: redéfinition de l'opérateur = sur point

                 gpx_dalle.debut.id_point= unMnt.lesPoints[i].id_point;
                 gpx_dalle.debut.x= unMnt.lesPoints[i].x;
                 gpx_dalle.debut.y= unMnt.lesPoints[i].y;

            }
        if(unMnt.lesPoints[i].x >= maxBounds.x && unMnt.lesPoints[i].y<= minBounds.y && unMnt.lesPoints[i].x<= gpx_dalle.fin.x && unMnt.lesPoints[i].y>= gpx_dalle.fin.y)

            {// remplace le point depart de dalle par le point de mnt: redéfinition de l'opérateur = sur point

                 gpx_dalle.fin.id_point= unMnt.lesPoints[i].id_point;
                 gpx_dalle.fin.x= unMnt.lesPoints[i].x;
                 gpx_dalle.fin.y= unMnt.lesPoints[i].y;

            }

    }

}

//calcule les identifiants des points  de la grille de Dalle et les stocke dans la tableau identifiants de DAlle
//Initialise aussi le nombre de colonne et de lignes de la grille de DAlle
void gpx::CalculateIndicePointsDalle(Mnt &unMnt)
{
    //initialisation des Zmin et Zmax de dalle
    gpx_dalle.z_min= unMnt.MAX_MNT.z;
    gpx_dalle.z_max=unMnt.MIN_MNT.z;

    int i=gpx_dalle.debut.id_point;
    int k=gpx_dalle.debut.id_point;
    gpx_dalle.nL_dalle=1;
    while(i+unMnt.nC<gpx_dalle.fin.id_point)
    {
        i=i+unMnt.nC;
        gpx_dalle.nL_dalle++;
    }

    gpx_dalle.nC_dalle=(gpx_dalle.fin.id_point)-i+1;

    while(k<gpx_dalle.fin.id_point)
    {
        for(int j=0;j<gpx_dalle.nC_dalle;j++)
           {
              gpx_dalle.id_sesPoints.push_back(k+j);
              if(unMnt.lesPoints[k+j].z<gpx_dalle.z_min)
                  gpx_dalle.z_min=unMnt.lesPoints[k+j].z;
              if(unMnt.lesPoints[k+j].z>gpx_dalle.z_max)
                  gpx_dalle.z_max=unMnt.lesPoints[k+j].z;


           }
        k=k+unMnt.nC;
    }



}
//construit une fausse trajectoire pour le test
void gpx::CalculateTrajectoire(Mnt &unMnt)
{
    for(int i=0;i<gpx_dalle.id_sesPoints.size();i++)
    {
        trajectoire.push_back(unMnt.lesPoints[gpx_dalle.id_sesPoints[i]-1]);

    }


}

void gpx::BuildTriangles(Mnt &unMnt)
{
    gpx_dalle.z_max_ses_triangles=0;
    gpx_dalle.z_min_ses_triangles=1000000;

    ///Construction des triangles de la dalle

   int nbr_triangle=1;
   //initializBounding();
   // nL= ((MAX_MNT.y-MIN_MNT.y)/pasY)+1;
   // nC= ((MAX_MNT.x-MIN_MNT.x)/pasX)+1;
   int cst=gpx_dalle.debut.id_point-1;
   //if()

    for(int j=0;j<gpx_dalle.nL_dalle-1;j++)
        {   for(int i=0;i<gpx_dalle.nC_dalle-1;i++)
            {
                Triangle t1,t2;
                t1.id_Triangle=nbr_triangle;
                t1.id_Sommet1=unMnt.lesPoints[i+(j*unMnt.nC)+cst].id_point;
                t1.id_Sommet2=unMnt.lesPoints[i+1+(j*unMnt.nC)+cst].id_point;
                t1.id_Sommet3=unMnt.lesPoints[i+unMnt.nC+(j*unMnt.nC)+cst].id_point;
                t1.z_moy=(unMnt.lesPoints[i+(j*unMnt.nC)+cst].z+unMnt.lesPoints[i+1+(j*unMnt.nC)+cst].z+unMnt.lesPoints[i+unMnt.nC+(j*unMnt.nC)+cst].z)/3;
                gpx_dalle.sesTriangles.push_back(t1);
                if(t1.z_moy> gpx_dalle.z_max_ses_triangles)
                     gpx_dalle.z_max_ses_triangles=t1.z_moy;
                if(t1.z_moy< gpx_dalle.z_min_ses_triangles)
                     gpx_dalle.z_min_ses_triangles=t1.z_moy;
                nbr_triangle++;
                //cout << "mon triangle"<<t1.id_Triangle<<" : "<<t1.id_Sommet1<<" "<<t1.id_Sommet2<<" "<<t1.id_Sommet3<<endl;
                t2.id_Triangle=nbr_triangle;
                t2.id_Sommet1=unMnt.lesPoints[i+1+(j*unMnt.nC)+cst].id_point;
                t2.id_Sommet2=unMnt.lesPoints[i+unMnt.nC+(j*unMnt.nC)+cst].id_point;
                t2.id_Sommet3=unMnt.lesPoints[i+1+unMnt.nC+(j*unMnt.nC)+cst].id_point;
                t2.z_moy=(unMnt.lesPoints[i+1+unMnt.nC+(j*unMnt.nC)+cst].z+unMnt.lesPoints[i+1+(j*unMnt.nC)+cst].z+unMnt.lesPoints[i+unMnt.nC+(j*unMnt.nC)+cst].z)/3;
                gpx_dalle.sesTriangles.push_back(t2);
                //cout << "mon triangle "<<t2.id_Triangle<<" : "<<t2.id_Sommet1<<" "<<t2.id_Sommet2<<" "<<t2.id_Sommet3<<endl;
                if(t2.z_moy> gpx_dalle.z_max_ses_triangles)
                     gpx_dalle.z_max_ses_triangles=t2.z_moy;
                if(t2.z_moy< gpx_dalle.z_min_ses_triangles)
                     gpx_dalle.z_min_ses_triangles=t2.z_moy;
                nbr_triangle++;
            }

        }


                cout<<"le nombre de triangles crées :"<<gpx_dalle.sesTriangles.size();
}


