#ifndef GPX_H
#define GPX_H

#include <vector>
#include "Point.h"
#include "dalle.h"
#include <string>
#include "mnt.h"
#include <QDebug>
#include <QString>
#include <QFile>

using namespace std;

class gpx
{
public:
    gpx();
    void loadGpx(QString fileName);

    std::vector<Point> ptsGpx;

    int dansQuelTriangle(Mnt& unMnt, Point p);
    bool estDansTriangle(Point p, Mnt& unMnt, int i);
    bool conditionDansTrianglePair(Point p, Mnt& mnt, int i);
    bool conditionDansTriangleImpair(Point p, Mnt& mnt, int i);
    void trouveInterSegment(Mnt mnt, Point a, int p);
    void inter(Mnt& mnt);
    double dist(Point a, Point b);
    void setZGpx(Mnt& mnt);
    double setZInter(Mnt& mnt, Point c, Point p1, Point p2, Point p3, int indTri);


    double minlat;
    double maxlat;
    double minlon;
    double maxlon;
    float minZ;
    float maxZ;
    vector<Point> trajectoire;
    Dalle gpx_dalle;
    void CalculateBoundsDalle(Mnt& unMnt); ////initialise dalle.debut par le point de MNT le plus proche à l'extrémité min du GPX
    void CalculateIndicePointsDalle(Mnt& unMnt); ////initialise dalle.debut par le point de MNT le plus proche à l'extrémité min du GPX
    void BuildTriangles(Mnt &unMnt);
    //
    void CalculateTrajectoire(Mnt &unMnt);

};

#endif // GPX_H
