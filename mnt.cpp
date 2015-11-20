#include "mnt.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;
Mnt::Mnt()
{
    MIN_MNT.z=100000000;
    MAX_MNT.z=-100000;
    pasX=-1;
    pasY=-1;
    MIN_MNT.x=100000000;
    MIN_MNT.y=100000000;

    MAX_MNT.x=-100000;
    MAX_MNT.y=-100000;
}

void Mnt::loadMnt(string fileName)
{
    //Lecture du fichier et construction des points et initialisation des bounds et pas
    std::cout << "loading " <<fileName << " : debut..." << std::endl;
    ifstream fichier( fileName.data() );
    int nb=0;
    int compteur=0;
    Point p;
    if(!fichier)
    {
        cout<<"une erreur s'est produite lors de l'ouverture du MNT"<<endl;
        return;
    }
    while(!fichier.eof())
    {
        //if(compteur%4==0)
        {

        if(fichier >> p.x>> p.y>>p.z)
        {
            nb++;
            p.id_point=nb;
            lesPoints.push_back(p);
            if(p.z<MIN_MNT.z) MIN_MNT.z=p.z;
            if(p.z>MAX_MNT.z) MAX_MNT.z=p.z;
            /*****/
            if(p.x<MIN_MNT.x) MIN_MNT.x=p.x;
            if(p.x>MAX_MNT.x) MAX_MNT.x=p.x;
            /*****/
            if(p.y<MIN_MNT.y) MIN_MNT.y=p.y;
            if(p.y>MAX_MNT.y) MAX_MNT.y=p.y;

            if(nb>=2 && (pasX==-1 || pasY==-1)) //initialisation du pas à la deuxième itération
            {
                if(p.x!=lesPoints[nb-2].x && pasX==-1) pasX=fabs(fabs(p.x)-fabs(lesPoints[0].x));
                if(p.y!=lesPoints[nb-2].y && pasY==-1) pasY=fabs(fabs(p.y)-fabs(lesPoints[0].y));
            }


        }

        }
        compteur++;

    }

    cout << "fin de lecture du fichier :"<<endl;
    cout << lesPoints.size()<<" Points construits"<<endl;
    fichier.close();

     nL= ((MAX_MNT.y-MIN_MNT.y)/pasY)+1;
     nC= ((MAX_MNT.x-MIN_MNT.x)/pasX)+1;

  }
void Mnt::initializBounding()
{
    //initiation des limites de l'étendu
    MIN_MNT.x=lesPoints[0].x;
    MIN_MNT.y=lesPoints[0].y;

    MAX_MNT.x=lesPoints[lesPoints.size()-1].x;
    MAX_MNT.y=lesPoints[lesPoints.size()-1].y;


}
/*void Mnt::CalculateBoundsDalle( Point minBounds, Point maxBounds) //initialize dalle.debut
{
    //initialisation
    //initialisation du debut de la dalle : par défaut c'est le début de MNT
    laDalle.debut.id_point= -1;
    laDalle.debut.x= lesPoints[0].x;
    laDalle.debut.y= lesPoints[0].y;
    //initialisation de la fin de la dalle : par défaut c'est la fin de MNT
    laDalle.fin.id_point= -1;
    laDalle.fin.x= lesPoints[lesPoints.size()-1].x;
    laDalle.fin.y= lesPoints[lesPoints.size()-1].y;
    //algo: Depart.x<minBounds.x et Depart.x est le plus grand possible (idem pour y)
    for(int i=0; i< lesPoints.size();i++)
    {
        if(lesPoints[i].x <= minBounds.x && lesPoints[i].y>= maxBounds.y && lesPoints[i].x>= laDalle.debut.x && lesPoints[i].y<= laDalle.debut.y)

            {// remplace le point depart de dalle par le point de mnt: redéfinition de l'opérateur = sur point

                 laDalle.debut.id_point= lesPoints[i].id_point;
                 laDalle.debut.x= lesPoints[i].x;
                 laDalle.debut.y= lesPoints[i].y;

            }
        if(lesPoints[i].x >= maxBounds.x && lesPoints[i].y<= minBounds.y && lesPoints[i].x<= laDalle.fin.x && lesPoints[i].y>= laDalle.fin.y)

            {// remplace le point depart de dalle par le point de mnt: redéfinition de l'opérateur = sur point

                 laDalle.fin.id_point= lesPoints[i].id_point;
                 laDalle.fin.x= lesPoints[i].x;
                 laDalle.fin.y= lesPoints[i].y;

            }

    }

}
void Mnt::BuildTriangles()
{


    ///Construction des triangles de la dalle

   int nbr_triangle=1;
   //initializBounding();
   // nL= ((MAX_MNT.y-MIN_MNT.y)/pasY)+1;
   // nC= ((MAX_MNT.x-MIN_MNT.x)/pasX)+1;
   int cst=laDalle.debut.id_point-1;
   //if()

    for(int j=0;j<laDalle.nL_dalle-1;j++)
        {   for(int i=0;i<laDalle.nC_dalle-1;i++)
            {
                Triangle t1,t2;
                t1.id_Triangle=nbr_triangle;
                t1.id_Sommet1=lesPoints[i+(j*nC)+cst].id_point;
                t1.id_Sommet2=lesPoints[i+1+(j*nC)+cst].id_point;
                t1.id_Sommet3=lesPoints[i+nC+(j*nC)+cst].id_point;
                laDalle.sesTriangles.push_back(t1);
                nbr_triangle++;
                //cout << "mon triangle"<<t1.id_Triangle<<" : "<<t1.id_Sommet1<<" "<<t1.id_Sommet2<<" "<<t1.id_Sommet3<<endl;
                t2.id_Triangle=nbr_triangle;
                t2.id_Sommet1=lesPoints[i+1+(j*nC)+cst].id_point;
                t2.id_Sommet2=lesPoints[i+nC+(j*nC)+cst].id_point;
                t2.id_Sommet3=lesPoints[i+1+nC+(j*nC)+cst].id_point;
                laDalle.sesTriangles.push_back(t2);
                //cout << "mon triangle "<<t2.id_Triangle<<" : "<<t2.id_Sommet1<<" "<<t2.id_Sommet2<<" "<<t2.id_Sommet3<<endl;
                nbr_triangle++;
            }

        }


    cout<<"le nombre de triangles crées :"<<laDalle.sesTriangles.size();
}
void Mnt::CalculateIndicePointsDalle()
{
    int i=laDalle.debut.id_point;
    int k=laDalle.debut.id_point;
    laDalle.nL_dalle=1;
    while(i+nC<laDalle.fin.id_point)
    {
        i=i+nC;
        laDalle.nL_dalle++;
    }
    //laDalle.nL_dalle++;
    laDalle.nC_dalle=(laDalle.fin.id_point)-i+1;

    while(k<laDalle.fin.id_point)
    {
        for(int j=0;j<laDalle.nC_dalle;j++)
            laDalle.id_sesPoints.push_back(k+j);
        k=k+nC;
    }



}
*/
