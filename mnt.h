#ifndef MNT_H
#define MNT_H
#define TAILLE_MAX 1024
#include "Point.h"
#include "triangle.h"
#include<iostream>
#include <vector>
#include <QGLViewer/qglviewer.h>

class Mnt
{
public:
    Mnt();
    void loadMnt(std::string fileName);
    void initializBounding();
    std::vector<Point> lesPoints ;
    std::vector<Triangle> lesTriangles ;
    qglviewer::Vec MIN_MNT;
    qglviewer::Vec MAX_MNT;
    float pasX;
    float pasY;



};

#endif // MNT_H
