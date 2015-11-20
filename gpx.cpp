#include "gpx.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QFile>
#include "help.h"
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

gpx::gpx()
{

}
void gpx::loadGpx(  QString filename){

    double lat=0;
    double lon = 0;
    bool b = false;
    QFile file(filename);
    QString name = "";
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open error:" << file.errorString();
    }
    QXmlStreamReader inputStream(&file);
    while (!inputStream.atEnd() && !inputStream.hasError())
    {
        inputStream.readNext();
        name = inputStream.name().toString();
        if (inputStream.isStartElement() && name == "trkpt") {
            lat = inputStream.attributes().value("lat").toDouble();
            lon = inputStream.attributes().value("lon").toDouble();
            inputStream.readNext();
            name = inputStream.name().toString();
            help::convertCoord(lon, lat);
            Point p;
            p.setX(lon);
            p.setY(lat);
            ptsGpx.push_back(p);
        }
        else if (!b && name=="bounds") {
                minlat = inputStream.attributes().value("minlat").toDouble();
                minlon = inputStream.attributes().value("minlon").toDouble();
                maxlat = inputStream.attributes().value("maxlat").toDouble();
                maxlon = inputStream.attributes().value("maxlon").toDouble();
                help::convertCoord(minlon, minlat);
                help::convertCoord(maxlon, maxlat);
                b = true;
            }
    }
}
void gpx::setZGpx(Mnt& mnt) {
    for (int i = 0; i<ptsGpx.size();i++){
        int indTri = dansQuelTriangle(mnt, ptsGpx[i]);
        if(indTri>-1) {
            Point p1 = mnt.lesPoints[gpx_dalle.sesTriangles[indTri].id_Sommet1 - 1];
            Point p2 = mnt.lesPoints[gpx_dalle.sesTriangles[indTri].id_Sommet2 - 1];
            Point p3 = mnt.lesPoints[gpx_dalle.sesTriangles[indTri].id_Sommet3 - 1];

            if(indTri%2==0){
                double xa = p1.getX();
                double ya = ptsGpx[i].getY();
                Point a = Point(xa, ya, 0);
                double za = (p3.getZ()*dist(a, p1)+p1.getZ()*dist(a, p3))/dist(p1, p3);
                a.setZ(za);
                double xb = p3.getX() + mnt.pasX/mnt.pasY * (ptsGpx[i].getY()-p3.getY());
                double yb = ptsGpx[i].getY();
                Point b = Point(xb, yb, 0);
                double zb = (p3.getZ()*dist(b, p2)+p2.getZ()*dist(b, p3))/dist(p2, p3);
                b.setZ(zb);
                if (xa!=xb || ya!=yb){
                    ptsGpx[i].z = (a.getZ()*dist(ptsGpx[i], b)+b.getZ()*dist(ptsGpx[i], a))/dist(a, b);
                }
                else {
                    ptsGpx[i].z = za;
                }
            }
            else{
                double xa = p1.getX();
                double ya = ptsGpx[i].getY();
                Point a = Point(xa, ya, 0);
                double za = (p3.getZ()*dist(a, p1)+p1.getZ()*dist(a, p3))/dist(p1, p3);
                a.setZ(za);
                double xb = p2.getX() + mnt.pasX/mnt.pasY * (ptsGpx[i].getY()-p2.getY());
                double yb = ptsGpx[i].getY();
                Point b = Point(xb, yb, 0);
                double zb = (p1.getZ()*dist(b, p2)+p2.getZ()*dist(b, p1))/dist(p2, p1);
                b.setZ(zb);
                if (xa!=xb || ya!=yb){
                    ptsGpx[i].z = (a.getZ()*dist(ptsGpx[i], b)+b.getZ()*dist(ptsGpx[i], a))/dist(a, b);
                }
                else {
                    ptsGpx[i].z = za;
                }
            }
        }
    }
}
double gpx::dist(Point a, Point b) {
    return (sqrt(pow(a.getX()-b.getX(), 2)+pow(a.getY()-b.getY(), 2)));
}

int gpx::dansQuelTriangle(Mnt& mnt, Point p) {
    for(int j = 0; j<gpx_dalle.sesTriangles.size(); j++) {
        if(estDansTriangle(p, mnt, j)){
            return j;
            break;
        }
    }
    if( (p.getX()==maxlon && p.getY()>=minlat) || (p.getY()==minlat && p.getX()<=maxlon)){
        return (gpx_dalle.sesTriangles.size()-1);
    }
    else{
        return -1;
    }
}
bool gpx::estDansTriangle(Point p, Mnt& mnt, int i) {
    if (i%2==0) {
        return conditionDansTrianglePair(p, mnt, i);
    }
    else {
        return conditionDansTriangleImpair(p, mnt, i);
    }
}
bool gpx::conditionDansTrianglePair(Point p, Mnt& mnt, int i) {
    Point p2 = mnt.lesPoints[gpx_dalle.sesTriangles[i].id_Sommet2 - 1];
    Point p3 = mnt.lesPoints[gpx_dalle.sesTriangles[i].id_Sommet3 - 1];
    return ( (  ( p.getX() >= p3.getX())
             && ( p.getY() <= p2.getY() )
             && ( p.getX() <= p2.getX() )
             && ( p.getY() >= p3.getY() )
             && (mnt.pasX * p.getY() - mnt.pasY * p.getX() > mnt.pasX * p2.getY() - mnt.pasY * p2.getX() -1/1000000) )
             || (p.getX()==p3.getX() && p.getY()==p3.getY())
             || (p.getX()==p2.getX() && p.getY()==p2.getY()));
}
bool gpx::conditionDansTriangleImpair(Point p, Mnt& mnt, int i) {
    Point p1 = mnt.lesPoints[gpx_dalle.sesTriangles[i].id_Sommet1 - 1];
    Point p2 = mnt.lesPoints[gpx_dalle.sesTriangles[i].id_Sommet2 - 1];
    return (    ( p.getX() > p2.getX())
             && ( p.getY() < p1.getY())
             && ( p.getX() < p1.getX())
             && ( p.getY() > p2.getY())
             && (mnt.pasX * p.getY() - mnt.pasY * p.getX() <= mnt.pasX * p2.getY() - mnt.pasY * p2.getX() +1/1000000) );
}
void gpx::trouveInterSegment(Mnt mnt, Point a, int p){
    //on trouve quel triangle est notre point de départ
    int indTri = dansQuelTriangle(mnt, a);

    if(indTri>=0){
        //on choisit des écritures adaptées
        Triangle t = gpx_dalle.sesTriangles[indTri];

        double x1 = mnt.lesPoints[t.id_Sommet1 -1].getX();
        double y1 = mnt.lesPoints[t.id_Sommet1 -1].getY();
        double z1 = mnt.lesPoints[t.id_Sommet1 -1].getZ();


        double x2 = mnt.lesPoints[t.id_Sommet2 -1].getX();
        double y2 = mnt.lesPoints[t.id_Sommet2 -1].getY();
        double z2 = mnt.lesPoints[t.id_Sommet2 -1].getZ();


        double x3 = mnt.lesPoints[t.id_Sommet3 -1].getX();
        double y3 = mnt.lesPoints[t.id_Sommet3 -1].getY();
        double z3 = mnt.lesPoints[t.id_Sommet3 -1].getZ();

        double xa = a.getX();
        double xb = ptsGpx[p+1].getX();

        double ya = a.getY();
        double yb = ptsGpx[p+1].getY();

        double px = mnt.pasX;
        double py = mnt.pasY;

        //on definie le vecteurs allant du point p au point p+1 du gpx
        double vx = xb - xa;
        double vy = yb - ya;

        //on definie les inconnues
        double interX1=0;
        double interY1=0;
        double interZ1=0;

        double interX2=0;
        double interY2=0;
        double interZ2=0;

        double interX3=0;
        double interY3=0;
        double interZ3=0;

        Point p1 = Point(x1, y1, z1);
        Point p2 = Point(x2, y2, z2);
        Point p3 = Point(x3, y3, z3);

        Point inter1;
        Point inter2;
        Point inter3;

        if (indTri%2==0) {

            interY1=y2;
            if (vy != 0){
                interX1=(vx*interY1-vx*ya+vy*xa)/vy;
                inter1 = Point(interX1, interY1, 0);
                interZ1=setZInter(mnt, inter1, p1, p2, p3, indTri);
                inter1.setZ(interZ1);
            }
            else {
                interX1=0;
                inter1 = Point(interX1, interY1, 0);
            }
            interX2=x3;
            if (vx != 0) {
                interY2=(vy*interX2+vx*ya-vy*xa)/vx;
                inter2 = Point(interX2, interY2, 0);
                interZ2= setZInter(mnt, inter2, p1, p2, p3, indTri);
                inter2.setZ(interZ2);
            }
            else {
                interY2=0;
                inter2 = Point(interX2, interY2, 0);
            }
            if (py*vx-vy*px!=0){
                interX3=(vx*px*y3-vx*py*x3+vy*xb*px-vx*px*yb)/(px*vy-py*vx);
                interY3=(px*y3-py*x3+py*interX3)/px;
                inter3 = Point(interX3, interY3, 0);
                interZ3= setZInter(mnt, inter3, p1, p2, p3, indTri);
                inter3.setZ(interZ3);
            }
            else{
                interY3 = 0;
                interX3 = 0;
                inter3 = Point(interX3, interY3, 0);
            }

            Point inter[3] = {inter1, inter2, inter3};

            float dmin = 10000;
            int aAjouter = -1;
            for(int i=0; i<3;i++){
                if(vx!=0 && vy!=0){
                    if ( (xb-inter[i].getX())/vx>0 && (yb-inter[i].getY())/vy>0 && (inter[i].getX()-xa)/vx>0 && (inter[i].getY()-ya)/vy>0 && inter[i].getZ()<= mnt.MAX_MNT.z){
                        float d = dist(a, inter[i]);
                        if (d<dmin){
                            aAjouter = i;
                        }
                    }
                }
                else if(vx!=0 && vy==0){
                    if(inter[i].getY()==yb && (xb-inter[i].getX())/vx>0 && (inter[i].getX()-xa)/vx>0){
                        float d = dist(a, inter[i]);
                        if (d<dmin){
                            aAjouter = i;
                        }
                    }
                }
                else if(vx==0 && vy!=0){
                    if(inter[i].getX()==xb && (yb-inter[i].getY())/vy>0 && (inter[i].getY()-ya)/vy>0){
                        float d = dist(a, inter[i]);
                        if (d<dmin){
                            aAjouter = i;
                        }
                    }
                }
            }
            if(aAjouter>-1){
                trajectoire.push_back(inter[aAjouter]);
                Point c = Point(inter[aAjouter].getX()+vx/100000, inter[aAjouter].getY()+vy/100000, 0);
                trouveInterSegment(mnt, c, p);
            }
        }


        if (indTri%2==1) {
            if (py*vx-vy*px!=0){
                interX1=(vx*px*yb-vy*px*xb+vx*py*x1-vx*px*y1)/(vx*py-vy*px);
                interY1=(py*interX1+px*y1-py*x1)/px;
                inter1 = Point(interX1, interY1, 0);
                interZ1= setZInter(mnt, inter1, p1, p2, p3, indTri);
                inter1.setZ(interZ1);
            }
            else{
                interY3 = 0;
                interX3 = 0;
                inter1 = Point(interX1, interY1, 0);
            }
            interY2=y2;
            if (vy != 0){
                interX2 = (vx*interY2-vx*yb+vy*xb)/vy;
                inter2 = Point(interX2, interY2, 0);
                interZ2 = setZInter(mnt, inter2, p1, p2, p3, indTri);
                inter2.setZ(interZ2);
            }
            else {
                interX2=0;
                inter2 = Point(interX2, interY2, 0);
            }
            interX3=x1;
            if (vx != 0){
                interY3=(vy*interX3+vx*yb-vy*xb)/vx;
                inter3 = Point(interX3, interY3, 0);
                interZ3= setZInter(mnt, inter3, p1, p2, p3, indTri);
                inter3.setZ(interZ3);
            }
            else {
                interY3=0;
                inter3=Point(interX3, interY3, 0);
            }

            Point inter[3] = {inter1, inter2, inter3};

            float dmin = 10000;
            int aAjouter = -1;
            for(int i=0; i<3;i++){
                if(vx!=0 && vy!=0){
                    if ( (xb-inter[i].getX())/vx>0 && (yb-inter[i].getY())/vy>0 && (inter[i].getX()-xa)/vx>0 && (inter[i].getY()-ya)/vy>0 && inter[i].getZ()<= mnt.MAX_MNT.z){
                        float d = dist(a, inter[i]);
                        if (d<dmin){
                            aAjouter = i;
                        }
                    }
                }
                else if(vx!=0 && vy==0){
                    if(inter[i].getY()==yb && (xb-inter[i].getX())/vx>0 && (inter[i].getX()-xa)/vx>0){
                        float d = dist(a, inter[i]);
                        if (d<dmin){
                            aAjouter = i;
                        }
                    }
                }
                else if(vx==0 && vy!=0){
                    if(inter[i].getX()==xb && (yb-inter[i].getY())/vy>0 && (inter[i].getY()-ya)/vy>0){
                        float d = dist(a, inter[i]);
                        if (d<dmin){
                            aAjouter = i;
                        }
                    }
                }
            }
            if(aAjouter>-1){
                trajectoire.push_back(inter[aAjouter]);
                Point c = Point(inter[aAjouter].getX()+vx/100000, inter[aAjouter].getY()+vy/100000, 0);
                trouveInterSegment(mnt, c, p);
            }
        }
    }
}
void gpx::inter(Mnt& mnt) {
    for(int i = 0; i<ptsGpx.size()-1; i++){
        if (ptsGpx[i].getX() >= gpx_dalle.debut.getX() && ptsGpx[i].getX() <= gpx_dalle.fin.getX() &&
            ptsGpx[i].getY() >= gpx_dalle.fin.getY() && ptsGpx[i].getY() <= gpx_dalle.debut.getY()    ) {
                trajectoire.push_back(ptsGpx[i]);
                trouveInterSegment(mnt, ptsGpx[i], i);
        }
    }
    trajectoire.push_back(ptsGpx[ptsGpx.size()-1]);
}




//méthodes Hanane
void gpx::CalculateBoundsDalle( Mnt &mnt) //initialize dalle.debut et fin
{
    //initialisation des points bounds
    Point minBounds, maxBounds;
            //ICI conversion des latitudes et longitudes à faire!!!!!!!
    minBounds.x=minlon;
    minBounds.y=minlat;

    maxBounds.x=maxlon;
    maxBounds.y=maxlat;

    //initialisation du debut de la dalle : par défaut c'est le début de MNT
    gpx_dalle.debut.id_point= 1;
    gpx_dalle.debut.x= mnt.lesPoints[0].x;
    gpx_dalle.debut.y= mnt.lesPoints[0].y;
    //initialisation de la fin de la dalle : par défaut c'est la fin de MNT
    gpx_dalle.fin.id_point= mnt.lesPoints.size();
    gpx_dalle.fin.x= mnt.lesPoints[mnt.lesPoints.size()-1].x;
    gpx_dalle.fin.y= mnt.lesPoints[mnt.lesPoints.size()-1].y;
    //algo: Depart.x<minBounds.x et Depart.x est le plus grand possible (idem pour y)
    for(int i=0; i< mnt.lesPoints.size();i++)
    {
        if(mnt.lesPoints[i].x <= minBounds.x && mnt.lesPoints[i].y>= maxBounds.y && mnt.lesPoints[i].x>= gpx_dalle.debut.x && mnt.lesPoints[i].y<= gpx_dalle.debut.y)

            {// remplace le point depart de dalle par le point de mnt: redéfinition de l'opérateur = sur point

                 gpx_dalle.debut.id_point= mnt.lesPoints[i].id_point;
                 gpx_dalle.debut.x= mnt.lesPoints[i].x;
                 gpx_dalle.debut.y= mnt.lesPoints[i].y;

            }
        if(mnt.lesPoints[i].x >= maxBounds.x && mnt.lesPoints[i].y<= minBounds.y && mnt.lesPoints[i].x<= gpx_dalle.fin.x && mnt.lesPoints[i].y>= gpx_dalle.fin.y)

            {// remplace le point depart de dalle par le point de mnt: redéfinition de l'opérateur = sur point

                 gpx_dalle.fin.id_point= mnt.lesPoints[i].id_point;
                 gpx_dalle.fin.x= mnt.lesPoints[i].x;
                 gpx_dalle.fin.y= mnt.lesPoints[i].y;

            }

    }

}

//calcule les identifiants des points  de la grille de Dalle et les stocke dans la tableau identifiants de DAlle
//Initialise aussi le nombre de colonne et de lignes de la grille de DAlle
void gpx::CalculateIndicePointsDalle(Mnt &mnt)
{
    //initialisation des Zmin et Zmax de dalle
    gpx_dalle.z_min= mnt.MAX_MNT.z;
    gpx_dalle.z_max=mnt.MIN_MNT.z;

    int i=gpx_dalle.debut.id_point;
    int k=gpx_dalle.debut.id_point;
    gpx_dalle.nL_dalle=1;
    while(i+mnt.nC<gpx_dalle.fin.id_point)
    {
        i=i+mnt.nC;
        gpx_dalle.nL_dalle++;
    }

    gpx_dalle.nC_dalle=(gpx_dalle.fin.id_point)-i+1;

    while(k<gpx_dalle.fin.id_point)
    {
        for(int j=0;j<gpx_dalle.nC_dalle;j++)
           {
              gpx_dalle.id_sesPoints.push_back(k+j);
              if(mnt.lesPoints[k+j].z<gpx_dalle.z_min)
                  gpx_dalle.z_min=mnt.lesPoints[k+j].z;
              if(mnt.lesPoints[k+j].z>gpx_dalle.z_max)
                  gpx_dalle.z_max=mnt.lesPoints[k+j].z;


           }
        k=k+mnt.nC;
    }



}
//construit une fausse trajectoire pour le test
void gpx::CalculateTrajectoire(Mnt &mnt)
{
    /*for(int i=0;i<gpx_dalle.id_sesPoints.size();i++)
    {
        trajectoire.push_back(mnt.lesPoints[gpx_dalle.id_sesPoints[i]-1]);

    }*/
    inter(mnt);


}

void gpx::BuildTriangles(Mnt &mnt)
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
                t1.id_Sommet1=mnt.lesPoints[i+(j*mnt.nC)+cst].id_point;
                t1.id_Sommet2=mnt.lesPoints[i+1+(j*mnt.nC)+cst].id_point;
                t1.id_Sommet3=mnt.lesPoints[i+mnt.nC+(j*mnt.nC)+cst].id_point;
                t1.z_moy=(mnt.lesPoints[i+(j*mnt.nC)+cst].z+mnt.lesPoints[i+1+(j*mnt.nC)+cst].z+mnt.lesPoints[i+mnt.nC+(j*mnt.nC)+cst].z)/3;
                gpx_dalle.sesTriangles.push_back(t1);
                if(t1.z_moy> gpx_dalle.z_max_ses_triangles)
                     gpx_dalle.z_max_ses_triangles=t1.z_moy;
                if(t1.z_moy< gpx_dalle.z_min_ses_triangles)
                     gpx_dalle.z_min_ses_triangles=t1.z_moy;
                nbr_triangle++;
                //cout << "mon triangle"<<t1.id_Triangle<<" : "<<t1.id_Sommet1<<" "<<t1.id_Sommet2<<" "<<t1.id_Sommet3<<endl;
                t2.id_Triangle=nbr_triangle;
                t2.id_Sommet1=mnt.lesPoints[i+1+(j*mnt.nC)+cst].id_point;
                t2.id_Sommet2=mnt.lesPoints[i+mnt.nC+(j*mnt.nC)+cst].id_point;
                t2.id_Sommet3=mnt.lesPoints[i+1+mnt.nC+(j*mnt.nC)+cst].id_point;
                t2.z_moy=(mnt.lesPoints[i+1+mnt.nC+(j*mnt.nC)+cst].z+mnt.lesPoints[i+1+(j*mnt.nC)+cst].z+mnt.lesPoints[i+mnt.nC+(j*mnt.nC)+cst].z)/3;
                gpx_dalle.sesTriangles.push_back(t2);
                //cout << "mon triangle "<<t2.id_Triangle<<" : "<<t2.id_Sommet1<<" "<<t2.id_Sommet2<<" "<<t2.id_Sommet3<<endl;
                if(t2.z_moy> gpx_dalle.z_max_ses_triangles)
                     gpx_dalle.z_max_ses_triangles=t2.z_moy;
                if(t2.z_moy< gpx_dalle.z_min_ses_triangles)
                     gpx_dalle.z_min_ses_triangles=t2.z_moy;
                nbr_triangle++;
            }

        }
}

double gpx::setZInter(Mnt& mnt,  Point c, Point p1, Point p2, Point p3, int indTri) {


            if(indTri%2==0){
                double xa = p1.getX();
                double ya = c.getY();
                Point a = Point(xa, ya, 0);
                double za = (p3.getZ()*dist(a, p1)+p1.getZ()*dist(a, p3))/dist(p1, p3);
                a.setZ(za);
                double yb = c.getY();
                double xb = p3.getX() + mnt.pasX/mnt.pasY * (c.getY()-p3.getY());
                Point b = Point(xb, yb, 0);
                double zb = (p3.getZ()*dist(b, p2)+p2.getZ()*dist(b, p3))/dist(p2, p3);
                b.setZ(zb);
                if (xa!=xb && c.getX() > xa && c.getX() < xb){
                    double z = (a.getZ()*dist(c, b)+b.getZ()*dist(c, a))/dist(a, b);
                    return (z);
                }
                else {
                    return za;
                }
            }
            else{
                double xa = p1.getX();
                double ya = c.getY();
                Point a = Point(xa, ya, 0);
                double za = (p3.getZ()*dist(a, p1)+p1.getZ()*dist(a, p3))/dist(p1, p3);
                a.setZ(za);
                double xb = p2.getX() + mnt.pasX/mnt.pasY * (c.getY()-p2.getY());
                double yb = c.getY();
                Point b = Point(xb, yb, 0);
                double zb = (p1.getZ()*dist(b, p2)+p2.getZ()*dist(b, p1))/dist(p2, p1);
                b.setZ(zb);
                if (xa!=xb && c.getX() > xa && c.getX() < xb){
                    double z = (a.getZ()*dist(c, b)+b.getZ()*dist(c, a))/dist(a, b);
                    return (z);
                }
                else {
                    return za;
                }
            }
}
