#ifndef MNT_H
#define MNT_H
#define TAILLE_MAX 1024
#include "Point.h"
#include "dalle.h"
#include "triangle.h"
#include<iostream>
#include <vector>
#include <QGLViewer/qglviewer.h>

class Mnt
{
public:
    Mnt();
    void loadMnt(std::string fileName);
    void BuildTriangles();
    void initializBounding();

    /*******/
    std::vector<Point> lesPoints ;
    std::vector<Triangle> lesTriangles ;
    qglviewer::Vec MIN_MNT;
    qglviewer::Vec MAX_MNT;
    float pasX;
    float pasY;
    bool isDisplayed=false;

    int nC;
    int nL;
    Dalle laDalle;



};

#endif // MNT_H
